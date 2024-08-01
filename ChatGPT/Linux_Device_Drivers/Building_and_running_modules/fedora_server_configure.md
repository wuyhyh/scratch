要在 Fedora Server 上配置环境进行 Linux 内核模块的开发，您需要完成以下步骤：

### 1. 安装必要的软件包
确保您的系统已经更新，并安装开发所需的软件包：
```bash
sudo dnf update
sudo dnf groupinstall "Development Tools"
sudo dnf install kernel-devel kernel-headers elfutils-libelf-devel
```

### 2. 获取和安装内核源码
您可能需要下载并安装与您当前运行内核版本匹配的内核源代码：
```bash
sudo dnf install kernel-devel-$(uname -r)
```

### 3. 编写一个简单的内核模块
创建一个简单的内核模块文件，例如 `hello.c`：
```c
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("吴宇航");
MODULE_DESCRIPTION("A simple Hello World LKM");
MODULE_VERSION("0.1");

static int __init hello_init(void) {
    printk(KERN_INFO "Hello, World!\n");
    return 0;
}

static void __exit hello_exit(void) {
    printk(KERN_INFO "Goodbye, World!\n");
}

module_init(hello_init);
module_exit(hello_exit);
```

### 4. 编写 Makefile
创建一个简单的 `Makefile` 文件，以便编译您的内核模块：
```Makefile
obj-m += hello.o

all:
    make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
    make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```

### 5. 编译和加载模块
在模块所在目录运行以下命令进行编译和加载：
```bash
make
sudo insmod hello.ko
```

### 6. 检查内核日志
使用 `dmesg` 命令检查内核日志，以验证模块是否已成功加载：
```bash
dmesg | tail
```

### 7. 卸载模块
完成测试后，可以卸载模块：
```bash
sudo rmmod hello
```

### 8. 使用 VSCode 进行开发
如果您希望在 VSCode 中进行开发，您可以使用 SSH 连接到您的 Fedora Server，并配置开发环境：

1. 打开 VSCode 并安装 Remote Development 插件。
2. 使用 Remote-SSH 连接到您的 Fedora Server。
3. 在 VSCode 中打开模块所在目录，并开始开发。

通过以上步骤，您可以在 Fedora Server 上配置环境，并进行 Linux 内核模块的开发。

有任何其他问题或需要进一步的帮助，请随时告知。