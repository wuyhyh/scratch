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
#include <linux/slab.h> // 内存管理的函数
#include <linux/types.h> // 设备号
#include <linux/cdev.h>
#include <asm/uaccess.h> // 在内核空间和用户空间之间拷贝数据

MODULE_LICENSE("GPL");
MODULE_AUTHOR("wyh");
MODULE_DESCRIPTION("A simple scull LKM");
MODULE_VERSION("0.1");

// 全局变量和宏定义
#define SCULL_QUANTUM 4000
#define SCULL_QSET 1000

int scull_major = 0;
int scull_minor = 0;
int scull_quantum = SCULL_QUANTUM;
int scull_qset = SCULL_QSET;

struct scull_dev *scull_devices;

// 设备方法
struct file_operations scull_fops {
	.owner = THIS_MODULE;
	.llseek = scull_llseek;
	.read = scull_read;
	.write = scull_write;
	.ioctl = scull_ioctl;
	.open = scull_open;
	.release = scull_release;
};

struct scull_qset {
	void **data;
	struct scull_qset *next;
};

// scull device
struct scull_dev {
	struct scull_qset *data;
	int quantum;
	int qset;
	unsigned long size;
	unsigned int access_key;
	struct semaphore sem;
	struct cdev cdev;
};

static void scull_setup_cdev(struct scull_dev *dev, int index)
{
	int err;
	int devno = MKDEV(scull_major, scull_minor + index);

	cdev_init(&dev->cdev, &scull_fops);
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops = &scull_fops;
	err = cdev_add(&dev->cdev, devno, 1);

	if (err)
		printk(KERN_NOTICE "Error %d adding scull%d", err, index);
}

int scull_open(struct inode *inode, struct file *filp)
{
	struct scull_dev *dev; // 设备信息

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
int scull_trim(struct scull_dev *dev)
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

// 实现ioctl方法
long scull_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	return 0;
}

// 实现scull_follow方法
struct scull_qset *scull_follow(struct scull_dev *dev, int n)
{
	struct scull_qset *qs = dev->data;

	if (!qs) {
		qs = dev->data = kmalloc(sizeof(struct scull_qset), GFP_KERNEL);
		if (qs == NULL)
			return NULL;
		memset(qs, 0, sizeof(struct scull_qset));
	}

	while (n--) {
		if (!qs->next) {
			qs->next =
				kmalloc(sizeof(struct scull_qset), GFP_KERNEL);
			if (qs->next == NULL) {
				return NULL;
			}
			memset(qs->next, 0, sizeof(struct scull_qset));
		}
		qs = qs->next;
	}

	return qs;
}

// read and write
ssize_t scull_read(struct file *filp, char __user *buf, size_t count,
		   loff_t *f_pos)
{
	struct scull_dev *dev = filp->private_data;
	struct scull_qset *dptr;
	int quantum = dev->quantum;
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

	if (dptr == NULL || !dptr->data || !dptr.data[s_pos]) {
		goto out;
	}

	if (count > quantum - q_pos) {
		count = quantum - q_pos;
	}

	if (copy_to_user(buf, dptr->data[s_pos] + q_pos, count)) {
		re_val = -EFAULT;
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
		re_val = -EFAULT;
		go_to out;
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

static int __init scull_init_module(void)
{
	printk(KERN_INFO "Hello, scull_module!\n");
	return 0;
}

static void __exit scull_cleanup_module(void)
{
	int i;
	dev_t devno = MKDEV(scull_major, scull_minor);

	if (scull_dev) {
		for (int i = 0; i < scull_nr_devs; ++i) {
			scull_trim(scull_dev);
			cdev_del(scull_dev->cdev);
		}
		kfree(scull_dev);
	}

	unregister_chrdev_region(devno);

	printk(KERN_INFO "Goodbye, scull_module!\n");
}

module_init(scull_init_module);
module_exit(scull_cleanup_module);
