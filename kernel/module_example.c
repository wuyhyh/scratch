/******************************************************************************
 *
 * Name: module_example.c - Description
 * Created on 2024/05/20
 * Copyright (C) 2022 - 2024, wyh.
 *
 *****************************************************************************/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init lkp_init(void)
{
	printk();
	return 0;
}

static void __exit lkp_exit(void)
{
	printk();
}

module_init(lkp_init);
module_exit(lkp_exit);

MODULE_LICENSE("GPL");
