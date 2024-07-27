在Linux内核中，磁盘和磁盘分区分别使用不同的数据结构来表示。这些数据结构主要包括 `gendisk` 结构和 `hd_struct` 结构。

### 磁盘数据结构：`gendisk`

`gendisk` 结构代表一个块设备（通常是一个磁盘）。

```c
struct gendisk {
    int major;                        // 主设备号
    int first_minor;                  // 第一个次设备号
    int minors;                       // 支持的次设备数
    char disk_name[DISK_NAME_LEN];    // 磁盘名称
    struct block_device_operations *fops; // 块设备操作
    struct request_queue *queue;      // 请求队列
    struct hd_geometry *geometry;     // 磁盘几何信息
    struct blk_integrity *integrity;  // 数据完整性支持
    struct kobject kobj;              // 关联的kobject
    struct kobject *slave_dir;        // 从属设备目录
    struct timer_list *event_timer;   // 事件定时器
    atomic_t sync_io;                 // 同步I/O计数
    struct backing_dev_info *bdi;     // 后备设备信息
    struct list_head part[0];         // 分区链表
};
```

### 主要字段解释

1. **major**：主设备号，用于唯一标识块设备的类型。
2. **first_minor**：第一个次设备号，用于标识设备的不同实例（如分区）。
3. **minors**：支持的次设备数。
4. **disk_name**：磁盘名称。
5. **fops**：指向块设备操作函数的指针，定义了对设备进行操作的接口。
6. **queue**：请求队列，管理对设备的I/O请求。
7. **geometry**：磁盘几何信息，如柱面、磁头和扇区数。
8. **integrity**：数据完整性相关信息。
9. **kobj**：关联的kobject，用于内核对象管理。
10. **slave_dir**：从属设备目录。
11. **event_timer**：事件定时器。
12. **sync_io**：同步I/O计数。
13. **bdi**：后备设备信息。
14. **part**：分区链表，包含所有的分区。

### 分区数据结构：`hd_struct`

`hd_struct` 结构代表磁盘上的一个分区。

```c
struct hd_struct {
    sector_t start_sect;       // 分区起始扇区
    sector_t nr_sects;         // 分区扇区数
    struct disk_stats __percpu *dkstats; // 分区统计信息
    struct percpu_ref ref;     // 引用计数
    struct rcu_work rcu_work;  // RCU工作
    struct kobject kobj;       // 关联的kobject
    struct list_head __rcu *holder_dir;  // 持有者目录
    int policy;                // 调度策略
    struct device __dev;       // 设备信息
    int partno;                // 分区号
    unsigned long alignment_offset; // 对齐偏移量
    unsigned int discard_alignment; // 丢弃对齐
    struct queue_limits limits;     // 队列限制
    char __devname[DISK_NAME_LEN];  // 设备名称
};
```

### 主要字段解释

1. **start_sect**：分区起始扇区，表示分区在磁盘上的起始位置。
2. **nr_sects**：分区扇区数，表示分区的大小。
3. **dkstats**：分区的统计信息，如读写操作次数。
4. **ref**：引用计数，用于管理分区的生命周期。
5. **rcu_work**：RCU工作，用于延迟销毁。
6. **kobj**：关联的kobject，用于内核对象管理。
7. **holder_dir**：持有者目录，存储相关的设备信息。
8. **policy**：调度策略。
9. **__dev**：设备信息。
10. **partno**：分区号，用于标识具体的分区。
11. **alignment_offset**：对齐偏移量，确保数据对齐。
12. **discard_alignment**：丢弃对齐，用于优化删除操作。
13. **limits**：队列限制，如最大传输大小。
14. **__devname**：设备名称。

### `gendisk` 和 `hd_struct` 之间的关系

`gendisk` 结构表示一个完整的磁盘设备，而 `hd_struct` 结构表示磁盘上的一个分区。一个 `gendisk` 可以包含多个 `hd_struct` 结构，每个 `hd_struct` 代表一个具体的分区。

### 数据结构之间的关联

1. **磁盘分区链表**：在 `gendisk` 结构中，`part` 字段用于链接所有的分区（`hd_struct`）。
2. **kobject**：`gendisk` 和 `hd_struct` 都包含 `kobject`，用于与内核的设备模型集成。

### 示例

以下是一个简单的代码示例，展示了如何初始化 `gendisk` 结构和添加分区：

```c
#include <linux/genhd.h>
#include <linux/blkdev.h>

static struct gendisk *mydisk;
static struct hd_struct *mypart;

static int __init mydisk_init(void) {
    mydisk = alloc_disk(1); // 分配gendisk结构
    if (!mydisk)
        return -ENOMEM;

    strcpy(mydisk->disk_name, "mydisk");
    mydisk->major = register_blkdev(0, "mydisk");
    mydisk->first_minor = 0;
    mydisk->fops = &mydisk_fops;
    mydisk->queue = blk_init_queue(my_request_fn, NULL);
    set_capacity(mydisk, 1024 * 2); // 设置磁盘容量为1024个扇区，即512KB
    add_disk(mydisk);

    // 分区初始化
    mypart = kzalloc(sizeof(*mypart), GFP_KERNEL);
    mypart->start_sect = 0;
    mypart->nr_sects = 1024;
    mydisk->part[0] = mypart;

    return 0;
}

static void __exit mydisk_exit(void) {
    del_gendisk(mydisk);
    put_disk(mydisk);
    blk_cleanup_queue(mydisk->queue);
    unregister_blkdev(mydisk->major, "mydisk");
    kfree(mypart);
}

module_init(mydisk_init);
module_exit(mydisk_exit);

MODULE_LICENSE("GPL");
```

这个示例展示了如何创建一个简单的块设备驱动程序，并初始化一个磁盘和一个分区。

希望这些信息对你有帮助！如果你有更多问题或需要进一步解释，请告诉我。