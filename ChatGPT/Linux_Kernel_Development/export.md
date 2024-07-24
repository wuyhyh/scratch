在Linux内核中，`export symbol`机制用于将内核模块中的符号（如变量和函数）导出，使得其他内核模块可以引用这些符号。这个机制通过一组内核宏和数据结构实现，确保模块之间的符号共享和依赖管理。下面是对这一机制的详细解释。

### `EXPORT_SYMBOL`宏

`EXPORT_SYMBOL`和`EXPORT_SYMBOL_GPL`是两个常用的宏，用于导出符号：

- `EXPORT_SYMBOL(symbol)`：将符号导出，使其可被任何内核模块引用。
- `EXPORT_SYMBOL_GPL(symbol)`：将符号导出，但仅允许GPL许可证下的模块引用。

```c
#include <linux/module.h>

int my_function(void) {
    // Function implementation
    return 0;
}

EXPORT_SYMBOL(my_function);
```

使用`EXPORT_SYMBOL`宏后，`my_function`可以被其他内核模块使用。

### 符号表

导出的符号被记录在内核的符号表中。每当内核模块被加载时，内核会检查该模块所需的符号是否在符号表中。如果所有依赖的符号都存在，模块就可以成功加载；否则加载会失败。

内核符号表通过数据结构`kallsyms`维护，包含所有导出的符号及其地址。这些符号在模块加载时用于解析符号引用。

### 运行时解析

当加载一个模块时，内核需要解析这个模块所依赖的符号。这是通过模块加载器完成的。模块加载器会查找所有导入的符号，并将它们与内核符号表中的导出符号进行匹配。如果找到匹配项，它会更新模块中的符号地址，从而解析符号依赖。

### 模块依赖性

导出符号机制还帮助管理模块之间的依赖性。例如，如果模块A依赖模块B中的某些符号，模块A必须在模块B之后加载。内核模块管理系统会确保这些依赖关系得以维护。

### 具体工作流程

1. **符号导出**：在模块源代码中使用`EXPORT_SYMBOL`宏导出符号。
2. **编译模块**：编译内核模块时，导出的符号会包含在模块的符号表中。
3. **加载模块**：加载模块时，内核会检查所有未解析的符号。
4. **符号解析**：内核模块加载器会将未解析的符号与内核符号表中的符号进行匹配。
5. **地址更新**：如果找到匹配项，加载器会更新模块中的符号地址。
6. **加载完成**：所有符号解析完成后，模块成功加载，并可以正常工作。

### 示例

假设有两个模块`module1`和`module2`，其中`module2`依赖于`module1`中的符号。

**module1.c**:
```c
#include <linux/module.h>
#include <linux/kernel.h>

int shared_function(void) {
    printk(KERN_INFO "Shared function called\n");
    return 0;
}

EXPORT_SYMBOL(shared_function);

static int __init module1_init(void) {
    printk(KERN_INFO "Module1 loaded\n");
    return 0;
}

static void __exit module1_exit(void) {
    printk(KERN_INFO "Module1 unloaded\n");
}

module_init(module1_init);
module_exit(module1_exit);

MODULE_LICENSE("GPL");
```

**module2.c**:
```c
#include <linux/module.h>
#include <linux/kernel.h>

extern int shared_function(void);

static int __init module2_init(void) {
    printk(KERN_INFO "Module2 loaded\n");
    shared_function();
    return 0;
}

static void __exit module2_exit(void) {
    printk(KERN_INFO "Module2 unloaded\n");
}

module_init(module2_init);
module_exit(module2_exit);

MODULE_LICENSE("GPL");
```

在这里，`module2`依赖于`module1`中的`shared_function`。在加载`module2`之前，必须先加载`module1`。

### 总结

Linux内核中的`export symbol`机制通过导出符号并将其记录在符号表中，允许内核模块之间共享函数和变量。该机制确保了模块之间的依赖关系和符号解析的正确性，使得内核模块化开发变得更加方便和高效。

### 参考资料

- [Linux Kernel Module Programming Guide](https://www.tldp.org/LDP/lkmpg/2.6/html/x569.html)
- [Linux Kernel Documentation](https://www.kernel.org/doc/html/latest/)
- [Understanding the Linux Kernel by Daniel P. Bovet and Marco Cesati](https://www.amazon.com/Understanding-Linux-Kernel-Daniel-Bovet/dp/0596005652)