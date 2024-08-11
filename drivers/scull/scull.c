/******************************************************************************
 *
 * Name: scull.c - Description
 * Created on 2024/08/02
 * Copyright (C) 2022 - 2024, wyh.
 *
 *****************************************************************************/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/slab.h>	 // 内存管理的函数
#include <linux/types.h> // 设备号
#include <linux/cdev.h>
#include <asm/uaccess.h> // 在内核空间和用户空间之间拷贝数据

#include "scull.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("wyh");
MODULE_DESCRIPTION("A simple scull LKM");
MODULE_VERSION("0.1");

// 全局变量和宏定义
#define SCULL_QUANTUM 4000
#define SCULL_QSET 1000
#define SCULL_NR_DEVS 4 // 设备数量

int scull_major = 0;
int scull_minor = 0;
int scull_quantum = SCULL_QUANTUM;
int scull_qset = SCULL_QSET;
int scull_nr_devs = SCULL_NR_DEVS;

struct scull_dev *scull_devices;

// 静态函数的声明
static int scull_trim(struct scull_dev *dev); // 释放数据区
static struct scull_qset *scull_follow(struct scull_dev *dev, int n); // 遍历数据区
static void scull_setup_cdev(struct scull_dev *dev, int index);
static void scull_cleanup_module(void);
static int __init scull_init(void);
static void __exit scull_exit(void);

// 设备方法：file_operations 结构保存了设备驱动程序的方法
struct file_operations scull_fops = {
	.owner = THIS_MODULE,
	.llseek = scull_llseek,
	.read = scull_read,
	.write = scull_write,
	.unlocked_ioctl = scull_ioctl,
	.open = scull_open,
	.release = scull_release,
};

// 实现文件偏移操作
loff_t scull_llseek(struct file *filp, loff_t off, int whence)
{
	struct scull_dev *dev = filp->private_data;
	loff_t new_pos;

	switch (whence) {
	case 0:
		new_pos = off;
		break;
	case 1:
		new_pos = filp->f_pos + off;
		break;
	case 2:
		new_pos = dev->size + off;
		break;
	default:
		return -EINVAL;
	}

	if (new_pos < 0)
		return -EINVAL;
	filp->f_pos = new_pos;
	return new_pos;
}

// read and write
ssize_t scull_read(struct file *filp, char __user *buf, size_t count,
		   loff_t *f_pos)
{
	struct scull_dev *dev = filp->private_data;
	struct scull_qset *dptr;
	int quantum = dev->quantum;
	int qset = dev->qset;
	int itemsize = quantum * qset;
	int item, s_pos, q_pos, rest;
	ssize_t retval = 0;

	if (down_interruptible(&dev->sem)) {
		return -ERESTARTSYS;
	}

	if (*f_pos >= dev->size) {
		goto out;
	}

	if (*f_pos + count > dev->size) {
		count = dev->size - *f_pos;
	}

	// 寻找链表项
	item = (long)*f_pos / itemsize;
	rest = (long)*f_pos % itemsize;
	s_pos = rest / quantum;
	q_pos = rest % quantum;

	dptr = scull_follow(dev, item);

	if (dptr == NULL || !dptr->data || !dptr->data[s_pos]) {
		goto out;
	}

	if (count > quantum - q_pos) {
		count = quantum - q_pos;
	}

	if (copy_to_user(buf, dptr->data[s_pos] + q_pos, count)) {
		retval = -EFAULT;
		goto out;
	}
	*f_pos += count;
	retval = count;

out:
	up(&dev->sem);
	return retval;
}

ssize_t scull_write(struct file *filp, const char __user *buf, size_t count,
		    loff_t *f_pos)
{
	struct scull_dev *dev = filp->private_data;
	struct scull_qset *dptr;
	int quantum = dev->quantum;
	int qset = dev->qset;
	int itemsize = quantum * qset;
	int item, s_pos, q_pos, rest;
	ssize_t retval = -ENOMEM;

	if (down_interruptible(&dev->sem)) {
		return -ERESTARTSYS;
	}

	item = (long)*f_pos / itemsize;
	rest = (long)*f_pos % itemsize;
	s_pos = rest / quantum;
	q_pos = rest * quantum;

	dptr = scull_follow(dev, item);
	if (dptr == NULL) {
		goto out;
	}
	if (!dptr->data) {
		dptr->data = kmalloc(qset * sizeof(char *), GFP_KERNEL);
		if (!dptr->data) {
			goto out;
		}
		memset(dptr->data, 0, qset * sizeof(char *));
	}
	if (!dptr->data[s_pos]) {
		dptr->data[s_pos] = kmalloc(quantum, GFP_KERNEL);
		if (!dptr->data[s_pos]) {
			goto out;
		}
	}

	if (count > quantum - q_pos) {
		count = quantum - q_pos;
	}

	if (copy_from_user(dptr->data[s_pos] + q_pos, buf, count)) {
		retval = -EFAULT;
		goto out;
	}
	*f_pos += count;
	retval = count;

	//更新文件大小
	if (dev->size < *f_pos) {
		dev->size = *f_pos;
	}

out:
	up(&dev->sem);
	return retval;
}

// 实现ioctl方法
long scull_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	return 0;
}

int scull_open(struct inode *inode, struct file *filp)
{
	struct scull_dev *dev;	  // 设备信息

	dev = container_of(inode->i_cdev, struct scull_dev, cdev);
	filp->private_data = dev; // for other dev methods

	if ((filp->f_flags & O_ACCMODE) == O_WRONLY) {
		scull_trim(dev);
	}

	return 0;
}

int scull_release(struct inode *inode, struct file *filp)
{
	return 0;
}

// 释放数据区
static int scull_trim(struct scull_dev *dev)
{
	struct scull_qset *next, *dptr;
	int qset = dev->qset;
	int i;

	for (dptr = dev->data; dptr; dptr = next) {
		if (dev->data) {
			for (i = 0; i < qset; i++) {
				kfree(dptr->data[i]);
			}
			kfree(dptr->data);
			dptr->data = NULL;
		}
		next = dptr->next;
		kfree(dptr);
	}
	dev->size = 0;
	dev->quantum = scull_quantum;
	dev->qset = scull_qset;
	dev->data = NULL;

	return 0;
}

// 实现scull_follow方法
static struct scull_qset *scull_follow(struct scull_dev *dev, int n)
{
	struct scull_qset *qset = dev->data;

	if (!qset) {
		qset = dev->data =
			kmalloc(sizeof(struct scull_qset), GFP_KERNEL);
		if (qset == NULL)
			return NULL;
		memset(qset, 0, sizeof(struct scull_qset));
	}

	while (n--) {
		if (!qset->next) {
			qset->next =
				kmalloc(sizeof(struct scull_qset), GFP_KERNEL);
			if (qset->next == NULL) {
				return NULL;
			}
			memset(qset->next, 0, sizeof(struct scull_qset));
		}
		qset = qset->next;
	}

	return qset;
}

/*
 * 实现初始化和清除函数
 * cdev_init() cdev_add() cdev_del() 方法是用来管理字符设备的函数
 * */
// 实现初始化函数
static void scull_setup_cdev(struct scull_dev *dev, int index)
{
	int err;
	int devno = MKDEV(scull_major, scull_minor + index);

	cdev_init(&dev->cdev, &scull_fops);
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops = &scull_fops;

	err = cdev_add(&dev->cdev, devno, 1);
	if (err) {
		printk(KERN_NOTICE "Error %d adding scull%d", err, index);
	}
}

// 实现清除函数
static void scull_cleanup_module(void)
{
	int i;
	dev_t devno = MKDEV(scull_major, scull_minor);

	if (scull_devices) {
		for (i = 0; i < scull_nr_devs; ++i) {
			scull_trim(scull_devices + i);
			cdev_del(&scull_devices[i].cdev);
		}
		kfree(scull_devices);
	}

	unregister_chrdev_region(devno, scull_nr_devs);

	printk(KERN_INFO "scull: module cleanup complete\n");
	// TODO: call the cleanup functions for friend devices
}

// 初始化和清理代码
static int __init scull_init(void)
{
	int result;
	int i;
	dev_t dev = 0;

	// 动态分配主设备号
	result = alloc_chrdev_region(&dev, scull_minor, scull_nr_devs, "scull");
	if (result < 0) {
		printk(KERN_WARNING, "scull: can't get major number\n");
		return result;
	}
	scull_major = MAJOR(dev);
	printk(KERN_INFO "scull: registered with major number %d\n",
	       scull_major);

	// 分配和初始化设备
	scull_devices =
		kmalloc(scull_nr_devs * sizeof(struct scull_dev), GFP_KERNEL);
	if (!scull_devices) {
		result = -ENOMEM;
		goto fail;
	}
	memset(scull_devices, 0, scull_nr_devs * sizeof(struct scull_dev));

	for (i = 0; i < scull_nr_devs; ++i) {
		scull_devices[i].quantum = scull_quantum;
		scull_devices[i].qset = scull_qset;
		sema_init(&scull_devices[i].sem, 1);
		scull_setup_cdev(&scull_devices[i], i);
	}

	printk(KERN_INFO "scull: module loaded\n");
	return 0;

fail:
	scull_cleanup_module();
	return result;
}

static void __exit scull_exit(void)
{
	scull_cleanup_module();
	printk(KERN_INFO "scull: module unloaded\n");
}

module_init(scull_init);
module_exit(scull_exit);
