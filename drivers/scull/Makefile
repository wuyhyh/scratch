# Makefile

# 指定内核源码路径
KDIR := /home/CLionProjects/scratch/linux-6.6.43
PWD := $(shell pwd)

# 内核模块的编译, 添加 scull.o 对象文件
obj-m += scull.o

# 默认目标，依次生成 build 目录、编译内核模块、编译用户态测试程序
all: build_dir build/scull.ko build/test_scull create_symbol_link

# 生成 build 目录
build_dir:
	@mkdir -p build

# 编译内核模块
# 查找所有 .c 和 .h 文件，如果有修改就重新编译
build/scull.ko: $(shell find . -name "*.c" -or -name "*.h")
	# 使用指定的内核源码路径和当前工作目录编译内核模块
	make -C $(KDIR) M=$(PWD) modules
	@chmod +x scull.ko

# 编译用户态测试程序
build/test_scull: CMakeLists.txt test_scull.c
	@mkdir -p build
	@cd build && cmake ..
	@cd build && make
	# 为生成的 test_scull 文件添加可执行权限
	@chmod +x build/test_scull

create_symbol_link: build/test_scull
	ln -s build/test_scull test_scull

# 清理目标，删除编译生成的文件和目录
clean:
	make -C $(KDIR) M=$(PWD) clean
	@rm -rf build
	@rm -rf test_scull

# 我们可以假设其他目录不存在，这样利用 scratch 项目构建的内核模块就简单了，没有必要使用单独的构建项目
