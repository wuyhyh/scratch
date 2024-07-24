在Linux内核中，常见的键值对数据结构（类似于用户空间中的map或dictionary）可以通过哈希表（hashtable）来实现。Linux内核提供了一套哈希表的API，可以用来实现这样的数据结构。主要的实现位于头文件 `linux/hashtable.h` 中。

### 哈希表的实现

内核中的哈希表是一个链地址法实现的哈希表，即哈希冲突时通过链表解决。以下是基本的哈希表实现和使用方法。

#### 定义和初始化哈希表

首先需要包含相关头文件：

```c
#include <linux/hashtable.h>
#include <linux/slab.h>
```

定义一个哈希表：

```c
DEFINE_HASHTABLE(my_hash_table, 10);
```

这里的 `10` 是哈希表的位数，表示哈希表的大小为 `2^10`。

#### 定义包含哈希表节点的结构体

```c
struct my_struct {
    int key;
    int value;
    struct hlist_node hash_node;
};
```

#### 插入元素

要插入元素，需要计算哈希值，并将元素添加到哈希表中：

```c
struct my_struct *new_entry = kmalloc(sizeof(struct my_struct), GFP_KERNEL);
new_entry->key = 42;
new_entry->value = 100;

hash_add(my_hash_table, &new_entry->hash_node, new_entry->key);
```

#### 查找元素

要查找元素，可以使用以下代码：

```c
struct my_struct *entry;
hash_for_each_possible(my_hash_table, entry, hash_node, 42) {
    if (entry->key == 42) {
        printk(KERN_INFO "Found entry with key 42, value: %d\n", entry->value);
    }
}
```

#### 删除元素

要从哈希表中删除元素：

```c
hash_del(&entry->hash_node);
kfree(entry);
```

### 示例代码

以下是一个完整的内核模块示例，演示了哈希表的使用：

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/hashtable.h>
#include <linux/slab.h>

struct my_struct {
    int key;
    int value;
    struct hlist_node hash_node;
};

DEFINE_HASHTABLE(my_hash_table, 10);

static int __init my_module_init(void)
{
    struct my_struct *new_entry;
    struct my_struct *entry;
    int i;

    // 插入元素
    for (i = 0; i < 5; i++) {
        new_entry = kmalloc(sizeof(struct my_struct), GFP_KERNEL);
        new_entry->key = i;
        new_entry->value = i * 100;
        hash_add(my_hash_table, &new_entry->hash_node, new_entry->key);
    }

    // 查找元素
    hash_for_each_possible(my_hash_table, entry, hash_node, 2) {
        if (entry->key == 2) {
            printk(KERN_INFO "Found entry with key 2, value: %d\n", entry->value);
        }
    }

    return 0;
}

static void __exit my_module_exit(void)
{
    struct my_struct *entry;
    struct hlist_node *tmp;
    int bkt;

    // 删除所有元素
    hash_for_each_safe(my_hash_table, bkt, tmp, entry, hash_node) {
        hash_del(&entry->hash_node);
        kfree(entry);
    }
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple example module using Linux kernel hash tables");
```

### 主要宏和函数

- `DEFINE_HASHTABLE(name, bits)`：定义一个哈希表，其中 `name` 是哈希表的名字，`bits` 是哈希表的位数（表大小为 `2^bits`）。
- `hash_add(hashtable, node, key)`：将元素添加到哈希表中，其中 `node` 是 `struct hlist_node` 类型的指针，`key` 是哈希键值。
- `hash_for_each_possible(hashtable, obj, member, key)`：遍历哈希表中所有可能匹配 `key` 的元素。
- `hash_del(node)`：从哈希表中删除元素。

通过这些宏和函数，Linux 内核提供了一个灵活且高效的哈希表实现，适用于各种需要键值对数据结构的场景。这些哈希表在内核的许多子系统中得到了广泛的应用，如进程管理、网络协议栈和设备驱动等。