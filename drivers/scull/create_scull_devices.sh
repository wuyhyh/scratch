#!/bin/bash

# 检查是否传入主设备号
if [ -z "$1" ]; then
    echo "Usage: $0 <major_number>"
    exit 1
fi

MAJOR_NUMBER=$1

# 删除现有的 scull 设备节点
rm -rf /dev/scull*

# 创建新的 scull 设备节点
mknod /dev/scull0 c $MAJOR_NUMBER 0
mknod /dev/scull1 c $MAJOR_NUMBER 1
mknod /dev/scull2 c $MAJOR_NUMBER 2
mknod /dev/scull3 c $MAJOR_NUMBER 3

# 设置权限
chmod 666 /dev/scull*

# 显示创建的设备节点
ls -l /dev | grep scull*
