`ioctl`（输入输出控制）是一种系统调用，用于与设备进行复杂的交互，特别是在需要传递复杂命令或数据结构的情况下。与 `seq_file` 接口主要用于读取和显示内核数据不同，`ioctl` 允许用户空间程序向内核模块发送命令，并且可以传递数据来控制设备行为或获取设备状态。

### 使用 `ioctl` 实现调试

#### 1. 定义 `ioctl` 命令

首先，在头文件中定义 `ioctl` 命令。通常使用宏来生成唯一的命令号。

```c
#ifndef IOCTL_EXAMPLE_H
#define IOCTL_EXAMPLE_H

#include <linux/ioctl.h>

// 定义 ioctl 命令
#define IOCTL_GET_MSG _IOR('i', 1, char *)
#define IOCTL_SET_MSG _IOW('i', 2, char *)
#define IOCTL_GET_INT _IOR('i', 3, int)
#define IOCTL_SET_INT _IOW('i', 4, int)

#endif // IOCTL_EXAMPLE_H
```

#### 2. 实现 `ioctl` 处理函数

在内核模块中实现 `ioctl` 处理函数。

```c
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include "ioctl_example.h"

#define DEVICE_NAME "ioctl_example"
#define BUFFER_SIZE 256

static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static long device_ioctl(struct file *, unsigned int, unsigned long);

static int major;
static char message[BUFFER_SIZE] = "Hello, ioctl!";
static int int_value = 42;

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = device_open,
    .release = device_release,
    .unlocked_ioctl = device_ioctl,
};

static int device_open(struct inode *inode, struct file *file) {
    return 0;
}

static int device_release(struct inode *inode, struct file *file) {
    return 0;
}

static long device_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    switch (cmd) {
        case IOCTL_GET_MSG:
            if (copy_to_user((char *)arg, message, sizeof(message))) {
                return -EACCES;
            }
            break;
        case IOCTL_SET_MSG:
            if (copy_from_user(message, (char *)arg, sizeof(message))) {
                return -EACCES;
            }
            break;
        case IOCTL_GET_INT:
            if (copy_to_user((int *)arg, &int_value, sizeof(int_value))) {
                return -EACCES;
            }
            break;
        case IOCTL_SET_INT:
            if (copy_from_user(&int_value, (int *)arg, sizeof(int_value))) {
                return -EACCES;
            }
            break;
        default:
            return -EINVAL;
    }
    return 0;
}

static int __init ioctl_example_init(void) {
    major = register_chrdev(0, DEVICE_NAME, &fops);
    if (major < 0) {
        printk(KERN_ALERT "Registering char device failed with %d\n", major);
        return major;
    }
    printk(KERN_INFO "I was assigned major number %d. To talk to\n", major);
    printk(KERN_INFO "the driver, create a dev file with\n");
    printk(KERN_INFO "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, major);
    return 0;
}

static void __exit ioctl_example_exit(void) {
    unregister_chrdev(major, DEVICE_NAME);
}

MODULE_LICENSE("GPL");
module_init(ioctl_example_init);
module_exit(ioctl_example_exit);
```

#### 3. 编写用户空间程序

在用户空间编写一个程序，使用 `ioctl` 与内核模块交互。

```c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "ioctl_example.h"

int main() {
    int fd;
    char message[BUFFER_SIZE];
    int value;

    fd = open("/dev/ioctl_example", O_RDWR);
    if (fd < 0) {
        perror("Failed to open the device...");
        return errno;
    }

    // Get message
    if (ioctl(fd, IOCTL_GET_MSG, message) == -1) {
        perror("Failed to get message from device...");
    } else {
        printf("Message from kernel: %s\n", message);
    }

    // Set message
    snprintf(message, BUFFER_SIZE, "New message from user space");
    if (ioctl(fd, IOCTL_SET_MSG, message) == -1) {
        perror("Failed to set message to device...");
    }

    // Get int
    if (ioctl(fd, IOCTL_GET_INT, &value) == -1) {
        perror("Failed to get int from device...");
    } else {
        printf("Integer value from kernel: %d\n", value);
    }

    // Set int
    value = 100;
    if (ioctl(fd, IOCTL_SET_INT, &value) == -1) {
        perror("Failed to set int to device...");
    }

    close(fd);
    return 0;
}
```

#### 4. 编译和加载模块

使用以下命令编译和加载内核模块：

```bash
make -C /lib/modules/$(uname -r)/build M=$(pwd) modules
sudo insmod ioctl_example.ko
```

创建设备文件：

```bash
sudo mknod /dev/ioctl_example c <major_number> 0
```

运行用户空间程序：

```bash
gcc -o ioctl_example_user ioctl_example_user.c
./ioctl_example_user
```

### `ioctl` 与 `seq_file` 的区别

- **用途**：
    - `seq_file` 主要用于实现连续读取的内核数据文件，适合大数据量的输出，通常用于 `/proc` 文件系统。
    - `ioctl` 用于在用户空间与内核空间之间传递复杂命令和数据，适合设备控制和状态获取。

- **数据交互**：
    - `seq_file` 是单向的，只能从内核读取数据到用户空间。
    - `ioctl` 是双向的，可以从用户空间向内核发送数据，也可以从内核读取数据到用户空间。

- **复杂度**：
    - `seq_file` 主要处理数据的读取过程，较为简单。
    - `ioctl` 可以处理更复杂的命令和数据结构，需要处理各种命令和相应的数据传递。

### 总结

`ioctl` 提供了一种强大的机制，可以在用户空间与内核模块之间进行复杂的交互，适合用于需要控制和配置设备的场景。而 `seq_file` 主要用于高效地读取和显示连续的内核数据。根据具体需求选择适合的机制，可以有效地实现内核调试和设备控制。