在 Linux 内核中，与主设备号和次设备号有关的函数主要用于字符设备和块设备的注册和管理。以下是一些常用的函数及其使用方法：

### 主要相关函数

1. **`register_chrdev_region`**
    - 用于注册一个字符设备区域（包括主设备号和次设备号范围）。
    - **原型**：
      ```c
      int register_chrdev_region(dev_t from, unsigned count, const char *name);
      ```
    - **参数**：
        - `from`：起始设备号（包括主设备号和次设备号）。
        - `count`：需要注册的次设备号数量。
        - `name`：设备名称。
    - **返回值**：成功时返回 0，失败时返回负值的错误代码。
    - **示例**：
      ```c
      dev_t dev;
      int major = 240;
      int minor = 0;
      int count = 1;
      dev = MKDEV(major, minor);
      if (register_chrdev_region(dev, count, "my_device") < 0) {
          printk(KERN_WARNING "my_device: can't get major %d\n", major);
      }
      ```

2. **`alloc_chrdev_region`**
    - 动态分配主设备号和次设备号。
    - **原型**：
      ```c
      int alloc_chrdev_region(dev_t *dev, unsigned baseminor, unsigned count, const char *name);
      ```
    - **参数**：
        - `dev`：指向设备号的指针，分配成功后保存主设备号和起始次设备号。
        - `baseminor`：次设备号的起始值。
        - `count`：需要分配的次设备号数量。
        - `name`：设备名称。
    - **返回值**：成功时返回 0，失败时返回负值的错误代码。
    - **示例**：
      ```c
      dev_t dev;
      int count = 1;
      if (alloc_chrdev_region(&dev, 0, count, "my_device") < 0) {
          printk(KERN_WARNING "my_device: can't allocate major number\n");
      }
      ```

3. **`unregister_chrdev_region`**
    - 注销已注册的设备号区域。
    - **原型**：
      ```c
      void unregister_chrdev_region(dev_t from, unsigned count);
      ```
    - **参数**：
        - `from`：起始设备号。
        - `count`：需要注销的次设备号数量。
    - **示例**：
      ```c
      dev_t dev;
      int major = 240;
      int minor = 0;
      int count = 1;
      dev = MKDEV(major, minor);
      unregister_chrdev_region(dev, count);
      ```

4. **`MKDEV`**
    - 用于创建一个设备号。
    - **原型**：
      ```c
      dev_t MKDEV(int major, int minor);
      ```
    - **参数**：
        - `major`：主设备号。
        - `minor`：次设备号。
    - **返回值**：组合后的设备号。
    - **示例**：
      ```c
      dev_t dev = MKDEV(240, 0);
      ```

5. **`MAJOR` 和 `MINOR`**
    - 用于从设备号中提取主设备号和次设备号。
    - **原型**：
      ```c
      int MAJOR(dev_t dev);
      int MINOR(dev_t dev);
      ```
    - **参数**：
        - `dev`：设备号。
    - **返回值**：主设备号或次设备号。
    - **示例**：
      ```c
      int major = MAJOR(dev);
      int minor = MINOR(dev);
      ```

### 示例代码

以下是一个简单的字符设备驱动示例，演示了如何使用这些函数：

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

#define DEVICE_NAME "my_device"

static dev_t dev;
static int major;

static int __init my_device_init(void)
{
    if (alloc_chrdev_region(&dev, 0, 1, DEVICE_NAME) < 0) {
        printk(KERN_WARNING "my_device: can't allocate major number\n");
        return -1;
    }

    major = MAJOR(dev);
    printk(KERN_INFO "my_device: registered with major number %d\n", major);
    return 0;
}

static void __exit my_device_exit(void)
{
    unregister_chrdev_region(dev, 1);
    printk(KERN_INFO "my_device: unregistered\n");
}

module_init(my_device_init);
module_exit(my_device_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple character device driver");
```

这个示例演示了如何动态分配设备号并在模块卸载时注销设备号。你可以根据需要扩展这个驱动程序，添加文件操作函数（如 `open`、`read`、`write` 等）和其他功能。