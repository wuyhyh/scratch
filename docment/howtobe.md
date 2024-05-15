# 怎样当好一个程序员

## 1. 版本控制工具

### 1.1 git

#### progit
https://git-scm.com/book/zh/v2

## 2.命令行环境

### 2.1 文件和目录

    ls -lts
    tree
    file <file_name>

### 2.2 进程

    ps -ef | grep <process_name>
    kill -9 <pid>
    ./a.out &

### 2.3 查找文件

    find <path> -name "file_name" -size <"+1G"> -or -type d

### 2.4 压缩文件

    tar -cz -f <target.tar.gz> <file1> <file2> <file3>

### 2.5 文本替换

    sed 's/origin/to_replace/g' <file_name>

### 2.6 内核驱动

    lsmod
    insmod <module.ko>
    modprobe <module>
    rmmod  <module>

## 3. 理论

### 3.1 编程语言

`The C programming language`

`计算机程序的构造和解释`

### 3.2 操作系统

`操作系统导论` https://github.com/remzi-arpacidusseau/ostep-code

`操作系统设计与实现`

`现代操作系统`

`Linux内核设计与实现`

`Linux内核完全注释`

`深入Linux内核架构`

`Linux设备驱动程序`

`Linux系统编程接口`

`Unix环境高级编程`

`Unix网络编程`

## 4. 构建工具

### 4.1 gcc

南洋理工：https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html

### 4.2 GNU make

GNU make官方文档：https://www.gnu.org/software/make/manual/make.pdf

跟我一起写Makefile：https://seisman.github.io/how-to-write-makefile/Makefile.pdf

### 4.3 Modern cmake

现代cmake: https://modern-cmake-cn.github.io/Modern-CMake-zh_CN/

英文版PDF：https://cliutils.gitlab.io/modern-cmake/modern-cmake.pdf

## 5. Linux基础

### 5.1 中科大Linux101

Linux101: https://101.lug.ustc.edu.cn/

## 6. 文档

### 6.1 markdown

https://roc-mountain.github.io/Markdown/

## 7. 项目

### 7.1 xv6项目

### 7.2 minix
