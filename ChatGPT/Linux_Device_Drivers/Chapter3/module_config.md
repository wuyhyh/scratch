在 Fedora Server 上配置内核模块开发环境涉及以下几个步骤：

1. **安装开发工具和内核源代码**：

   你需要安装一些必要的开发工具和内核源代码包。运行以下命令：

   ```bash
   sudo dnf groupinstall "Development Tools"
   sudo dnf install kernel-devel kernel-headers
   ```

2. **验证内核版本**：

   确保你安装的内核开发包版本与正在运行的内核版本匹配。你可以使用以下命令查看当前运行的内核版本：

   ```bash
   uname -r
   ```

   然后查看已安装的内核开发包版本：

   ```bash
   rpm -q kernel-devel
   rpm -q kernel-headers
   ```

   如果版本不匹配，可能需要安装匹配的版本或更新系统内核。

3. **创建内核模块源代码**：

   创建一个新的目录来保存你的内核模块源代码文件。例如：

   ```bash
   mkdir ~/Kernel_Modules
   cd ~/Kernel_Modules
   ```

   然后创建一个简单的内核模块文件 `hello.c`：

   ```c
   // hello.c
   #include <linux/init.h>
   #include <linux/module.h>
   #include <linux/kernel.h>

   MODULE_LICENSE("GPL");
   MODULE_AUTHOR("Your Name");
   MODULE_DESCRIPTION("A simple hello world kernel module");
   MODULE_VERSION("1.0");

   static int __init hello_init(void) {
       printk(KERN_INFO "Hello, world!\n");
       return 0;
   }

   static void __exit hello_exit(void) {
       printk(KERN_INFO "Goodbye, world!\n");
   }

   module_init(hello_init);
   module_exit(hello_exit);
   ```

4. **编写 Makefile**：

   创建一个 Makefile 来编译内核模块：

   ```makefile
   # Makefile
   obj-m += hello.o

   all:
       make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

   clean:
       make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
   ```

5. **编译内核模块**：

   在模块目录中运行 `make` 命令以编译模块：

   ```bash
   make
   ```

   这将生成一个 `hello.ko` 文件，这是你的内核模块。

6. **加载和卸载内核模块**：

   使用 `insmod` 命令加载模块：

   ```bash
   sudo insmod hello.ko
   ```

   使用 `lsmod` 命令确认模块是否已加载：

   ```bash
   lsmod | grep hello
   ```

   查看内核日志以确认模块信息：

   ```bash
   dmesg | tail
   ```

   使用 `rmmod` 命令卸载模块：

   ```bash
   sudo rmmod hello
   ```

   再次查看内核日志确认模块已卸载：

   ```bash
   dmesg | tail
   ```

这样，你就完成了在 Fedora Server 上配置内核模块开发环境的步骤。