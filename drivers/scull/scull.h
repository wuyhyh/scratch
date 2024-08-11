/******************************************************************************
 *
 * Name: scull.h - Description
 * Created on 2024/08/11
 * Copyright (C) 2022 - 2024, wyh.
 *
 *****************************************************************************/

#ifndef SCULL_H
#define SCULL_H

// 设备的数据
struct scull_qset {
	void **data;              /* Array of pointers to data blocks. */
	struct scull_qset *next;  /* Pointer to the next quantum set in the list. */
};

// 设备文件，struct file表示一个打开的文件，而struct inode表示一个磁盘上的文件
struct scull_dev {
	struct scull_qset *data;     /* Pointer to the first quantum set. */
	int quantum;                 /* The size of each quantum (data block). */
	int qset;                    /* The number of quantums in each quantum set. */
	unsigned long size;          /* The total size of the data stored in the device. */
	unsigned int access_key;     /* Key for access control. */
	struct semaphore sem;        /* Semaphore for mutual exclusion. */
	struct cdev cdev;            /* Character device structure for kernel interaction. */
};

/* 设备公开的方法 */
loff_t scull_llseek(struct file *filp, loff_t off, int whence);
ssize_t scull_read(struct file *filp, char __user *buf, size_t count,
		   loff_t *f_pos);
ssize_t scull_write(struct file *filp, const char __user *buf, size_t count,
		    loff_t *f_pos);
long scull_ioctl(struct file *filp, unsigned int cmd, unsigned long arg);
int scull_open(struct inode *inode, struct file *filp);
int scull_release(struct inode *inode, struct file *filp);

#endif SCULL_H
