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

MODULE_LICENSE("GPL");
MODULE_AUTHOR("wyh");
MODULE_DESCRIPTION("A simple scull LKM");
MODULE_VERSION("0.1");

/*
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
*/
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
