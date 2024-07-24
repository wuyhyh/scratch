页描述符（Page Descriptor），在Linux内核中称为 `struct page`，用于描述每个物理页帧。其大小在32位和64位系统上是不同的，主要原因是指针大小和数据对齐要求的差异。以下是具体的细节：

### 32位系统上的页描述符

在32位系统上，指针大小是4字节。页描述符的大小通常在32字节左右。具体大小取决于内核版本和配置，但通常包含以下字段：

- 指向页框的指针
- 页框的标志位
- 引用计数
- 其他内核数据结构的指针，如进程、内存区域等

由于32位系统地址空间较小，页描述符不需要太多额外信息，因此结构相对紧凑。

### 64位系统上的页描述符

在64位系统上，指针大小是8字节。页描述符的大小通常在56字节到64字节左右，具体取决于内核版本和配置。64位系统的页描述符通常包含与32位系统相同的字段，但由于指针变大，结构体的大小也相应增加。

### 示例：页描述符的结构

以下是一个简化的页描述符（`struct page`）示例：

```c
struct page {
    unsigned long flags;          /* 标志位 */
    atomic_t _count;              /* 引用计数 */
    atomic_t _mapcount;           /* 页框映射计数 */
    unsigned long private;        /* 私有数据 */
    struct address_space *mapping;/* 地址空间指针 */
    pgoff_t index;                /* 页框索引 */
    struct list_head lru;         /* LRU链表 */
    /* 更多字段 */
};
```

### 具体差异

- **指针大小**：在64位系统上，指针字段（如 `mapping`）占用8字节，而在32位系统上占用4字节。
- **对齐要求**：64位系统可能有更严格的对齐要求，导致结构体填充（padding），使得结构体变大。

### 实际大小查看

可以通过一些调试工具或命令查看实际的 `struct page` 大小。例如：

```sh
cat /proc/kallsyms | grep struct_page
```

或通过编写简单的内核模块打印 `struct page` 的大小：

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/mm.h>

static int __init my_module_init(void) {
    printk(KERN_INFO "Size of struct page: %zu\n", sizeof(struct page));
    return 0;
}

static void __exit my_module_exit(void) {
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Print struct page size");
MODULE_AUTHOR("Your Name");
```

在编译并加载此模块后，可以在内核日志中看到 `struct page` 的大小。

### 总结

32位和64位系统上的页描述符大小确实有差异，主要是由于指针大小和对齐要求不同。了解这些差异对于优化内核内存管理和调试内核相关问题非常有帮助。如果有更具体的需求或问题，欢迎进一步提问。