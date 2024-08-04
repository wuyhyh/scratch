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

	if (cope_to_user(buf, dptr->data[s_pos] + q_pos, count)) {
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

static int __init scull_init(void)
{
	printk(KERN_INFO "Hello, scull!\n");
	return 0;
}

static void __exit scull_exit(void)
{
	printk(KERN_INFO "Goodbye, scull!\n");
}

module_init(scull_init);
module_exit(scull_exit);
