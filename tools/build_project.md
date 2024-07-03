组织一个大型系统软件，其中内核态代码使用Makefile而用户态代码使用CMake，可以通过分离项目结构、使用顶层管理脚本以及合理组织各自的构建系统来实现。下面是详细的步骤和示例。

### 项目结构

首先，定义一个合理的项目结构，以便清晰地分离内核态代码和用户态代码。以下是一个示例结构：

```
project_root/
├── kernel/
│   ├── Makefile
│   ├── src/
│   ├── include/
│   └── ...
├── user/
│   ├── CMakeLists.txt
│   ├── src/
│   ├── include/
│   └── ...
├── CMakeLists.txt
└── build/
```

### 内核态代码使用Makefile

在`kernel/`目录下，创建一个适用于内核代码的Makefile。假设你有一个简单的内核模块：

```makefile
# kernel/Makefile

KERNEL_SRC := $(wildcard src/*.c)
KERNEL_OBJ := $(KERNEL_SRC:.c=.o)

# Specify the kernel source tree
KERNELDIR ?= /lib/modules/$(shell uname -r)/build

# Output directory
OUTDIR := build

# Module name
MODULE := my_kernel_module

all: $(MODULE).ko

$(MODULE).ko: $(KERNEL_OBJ)
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm -rf $(OUTDIR)/*.o $(OUTDIR)/*.ko

.PHONY: all clean
```

### 用户态代码使用CMake

在`user/`目录下，使用CMakeLists.txt来管理用户态代码的构建：

```cmake
# user/CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(UserApp)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Executable
add_executable(user_app ${SOURCES})
```

### 顶层CMakeLists.txt

在项目根目录下，创建一个顶层的CMakeLists.txt，用于管理整个项目并调用用户态部分的CMake文件：

```cmake
# CMakeLists.txt at project_root

cmake_minimum_required(VERSION 3.10)
project(ProjectRoot)

add_subdirectory(user)
```

### 构建和管理脚本

在项目根目录下，编写一个脚本来构建内核态和用户态代码。例如，创建一个名为`build.sh`的脚本：

```bash
#!/bin/bash

# Build kernel module
echo "Building kernel module..."
make -C kernel

# Build user application
echo "Building user application..."
mkdir -p build
cd build
cmake ..
make
```

### 使用脚本构建项目

1. 给脚本执行权限：

   ```bash
   chmod +x build.sh
   ```

2. 执行脚本：

   ```bash
   ./build.sh
   ```

### 总结

通过上述方法，你可以有效地组织一个大型系统软件，其中内核态代码使用Makefile，用户态代码使用CMake。这样做的好处是，内核态和用户态代码的构建系统彼此独立，维护起来更加方便，同时顶层管理脚本可以统一管理整个项目的构建过程。