/******************************************************************************
 *
 * Name: hello.c - Description
 * Created on 2024/08/01
 * Copyright (C) 2022 - 2024, wyh.
 *
 *****************************************************************************/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("wyh");
MODULE_DESCRIPTION("A simple Hello World LKM");
MODULE_VERSION("0.1");

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
