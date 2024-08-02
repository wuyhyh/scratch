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

MODULE_LICENSE("GPL");
MODULE_AUTHOR("wyh");
MODULE_DESCRIPTION("A simple Hello World LKM");
MODULE_VERSION("0.1");

static int __init hello_init(void)
{
	printk(KERN_INFO "Hello, World!\n");
	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_INFO "Goodbye, World!\n");
}

module_init(hello_init);
module_exit(hello_exit);
