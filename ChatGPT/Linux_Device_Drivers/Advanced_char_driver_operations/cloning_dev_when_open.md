在 Linux 内核中，实现打开时复制设备（即每次打开设备文件时为其分配独立的资源）涉及为每个打开实例分配独立的内存或其他资源。这通常通过在设备文件的 `open` 方法中动态分配内存，并在 `file` 结构的 `private_data` 字段中存储指向该内存的指针来实现。关闭设备文件时，需要释放这些分配的资源。

以下是详细的实现步骤和示例代码：

### 实现步骤

1. **定义设备数据结构**：定义一个结构体来保存每个设备实例的私有数据。
2. **在 `open` 方法中分配内存**：在设备文件的 `open` 方法中，为每个打开的设备实例分配内存，并初始化该内存。
3. **在 `release` 方法中释放内存**：在设备文件的 `release` 方法中，释放分配的内存。
4. **在 `read` 和 `write` 方法中使用私有数据**：在设备文件的 `read` 和 `write` 方法中，使用 `file->private_data` 访问每个实例的私有数据。

### 示例代码

#### 头文件和宏定义

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/mutex.h>

#define DEVICE_NAME "mychardev"
#define BUF_LEN 1024

static int major;
static DEFINE_MUTEX(device_mutex);

struct my_device_data {
    char *buffer;
    size_t size;
};
```

#### 打开和关闭设备文件

```c
static int device_open(struct inode *inode, struct file *file) {
    struct my_device_data *data;

    data = kmalloc(sizeof(struct my_device_data), GFP_KERNEL);
    if (!data)
        return -ENOMEM;

    data->buffer = kmalloc(BUF_LEN, GFP_KERNEL);
    if (!data->buffer) {
        kfree(data);
        return -ENOMEM;
    }

    data->size = 0;
    file->private_data = data;

    try_module_get(THIS_MODULE);
    return 0;
}

static int device_release(struct inode *inode, struct file *file) {
    struct my_device_data *data = file->private_data;

    kfree(data->buffer);
    kfree(data);
    module_put(THIS_MODULE);
    return 0;
}
```

#### 读和写方法

```c
static ssize_t device_read(struct file *file, char __user *buffer, size_t len, loff_t *offset) {
    struct my_device_data *data = file->private_data;
    ssize_t bytes_read = 0;

    if (*offset >= data->size)
        return 0;

    if (*offset + len > data->size)
        len = data->size - *offset;

    if (copy_to_user(buffer, data->buffer + *offset, len))
        return -EFAULT;

    *offset += len;
    bytes_read = len;

    return bytes_read;
}

static ssize_t device_write(struct file *file, const char __user *buffer, size_t len, loff_t *offset) {
    struct my_device_data *data = file->private_data;
    ssize_t bytes_written = 0;

    if (*offset >= BUF_LEN)
        return 0;

    if (*offset + len > BUF_LEN)
        len = BUF_LEN - *offset;

    if (copy_from_user(data->buffer + *offset, buffer, len))
        return -EFAULT;

    *offset += len;
    bytes_written = len;

    if (data->size < *offset)
        data->size = *offset;

    return bytes_written;
}
```

#### `llseek` 方法

```c
static loff_t device_llseek(struct file *file, loff_t offset, int whence) {
    struct my_device_data *data = file->private_data;
    loff_t new_pos = 0;

    switch (whence) {
        case SEEK_SET:
            new_pos = offset;
            break;
        case SEEK_CUR:
            new_pos = file->f_pos + offset;
            break;
        case SEEK_END:
            new_pos = data->size + offset;
            break;
        default:
            return -EINVAL;
    }

    if (new_pos < 0 || new_pos > BUF_LEN)
        return -EINVAL;

    file->f_pos = new_pos;
    return new_pos;
}
```

#### 文件操作结构体和模块初始化

```c
static struct file_operations fops = {
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_release,
    .llseek = device_llseek,
};

static int __init my_init(void) {
    dev_t dev_num;
    int ret;

    ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
    if (ret < 0) {
        printk(KERN_ALERT "alloc_chrdev_region failed with %d\n", ret);
        return ret;
    }

    major = MAJOR(dev_num);

    cdev_init(&my_cdev, &fops);
    ret = cdev_add(&my_cdev, dev_num, 1);
    if (ret < 0) {
        unregister_chrdev_region(dev_num, 1);
        printk(KERN_ALERT "cdev_add failed with %d\n", ret);
        return ret;
    }

    printk(KERN_INFO "I was assigned major number %d. To talk to\n", major);
    printk(KERN_INFO "the driver, create a dev file with\n");
    printk(KERN_INFO "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, major);
    return 0;
}

static void __exit my_exit(void) {
    dev_t dev_num = MKDEV(major, 0);

    cdev_del(&my_cdev);
    unregister_chrdev_region(dev_num, 1);
    printk(KERN_INFO "Goodbye, world!\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple char device driver with instance-specific data");
```

### 需要注意的事项

1. **内存管理**：确保在设备文件打开时分配的内存在设备文件关闭时正确释放，以避免内存泄漏。
2. **并发控制**：如果设备文件可能被多个进程同时访问，确保对私有数据的访问是线程安全的。
3. **错误处理**：在分配内存失败时，返回适当的错误码并进行必要的清理工作。
4. **实例化私有数据**：确保每次打开设备文件时都创建新的实例，并在 `file->private_data` 中存储指向该实例的指针。

通过这种方式，可以实现每次打开设备文件时为其分配独立的资源，从而实现设备文件的“打开时复制”行为。如果有其他问题或需要进一步的解释，请随时告诉我。