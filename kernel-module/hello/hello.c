/******************************************************************************
 *
 * Name: hw.c - Description
 * Created on 2024/06/18
 * Copyright (C) 2022 - 2024, wyh.
 *
 *****************************************************************************/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init hello_init(void) {
	printk(KERN_INFO "Hello, World!\n");
	return 0;
}

static void __exit hello_exit(void) {
	printk(KERN_INFO "Goodbye, World!\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple Hello World Module");
