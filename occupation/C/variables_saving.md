在C语言中，变量在内存中的存储方式取决于它们的存储类型和初始化情况。内存通常划分为多个段，包括代码段、数据段、BSS段、堆和栈。不同类型的变量会被分配到不同的内存区域。

内存分段

在C程序的执行过程中，内存通常会被分成以下几段：

	1.	代码段（Text Segment）：存储程序的可执行代码，通常是只读的。
	2.	数据段（Data Segment）：用于存储已初始化的全局变量和静态变量。
	3.	BSS段（Block Started by Symbol）：用于存储未初始化的全局变量和静态变量。
	4.	堆（Heap）：用于动态内存分配，由malloc、calloc等函数分配，free释放。
	5.	栈（Stack）：用于存储局部变量、函数参数和返回地址，通常在函数调用时分配，函数返回时释放。

各类型变量的内存存储

	1.	全局变量：
	•	已初始化的全局变量存储在数据段（Data Segment）中。
	•	未初始化的全局变量存储在BSS段中。未初始化的全局变量在程序加载时会自动初始化为0。
	2.	静态变量：
	•	与全局变量类似，静态变量在程序加载时分配存储空间，并在程序结束时释放。
	•	已初始化的静态变量存储在数据段。
	•	未初始化的静态变量存储在BSS段，同样在程序加载时自动初始化为0。
	3.	局部变量：
	•	普通局部变量存储在栈中，在函数调用时分配，函数返回时释放。
	•	局部变量没有默认初始化值，其值是不确定的。
	4.	动态内存分配变量：
	•	使用malloc、calloc、realloc等函数分配的变量存储在堆上，需要手动释放。

示例代码
```c
#include <stdio.h>
#include <stdlib.h>

int global_var;		  // 未初始化全局变量（存放在BSS段）
int global_init_var = 10; // 已初始化全局变量（存放在数据段）

void func()
{
	static int static_var;		// 未初始化静态变量（BSS段）
	static int static_init_var = 5; // 已初始化静态变量（数据段）
	int local_var = 0;		// 局部变量（栈中）
	int *dynamic_var = malloc(sizeof(int)); // 动态分配变量（堆中）
	*dynamic_var = 20;
	printf("Local Variable: %d\n", local_var);
	printf("Dynamic Variable: %d\n", *dynamic_var);
	free(dynamic_var); // 释放动态分配的内存
}

int main()
{
	func();
	return 0;
}

```
内存段分配概述

	•	BSS段：global_var（未初始化的全局变量）、static_var（未初始化的静态变量）都存放在这里。
	•	数据段：global_init_var（已初始化的全局变量）、static_init_var（已初始化的静态变量）存放在这里。
	•	栈：local_var存储在栈中，每次调用func()时会重新分配。
	•	堆：dynamic_var通过malloc分配在堆上，且必须手动释放。

总结

	•	BSS段：未初始化的全局和静态变量，程序加载时初始化为0。
	•	数据段：已初始化的全局和静态变量。
	•	栈：局部变量和函数调用信息。
	•	堆：动态分配的内存，需要手动管理。
