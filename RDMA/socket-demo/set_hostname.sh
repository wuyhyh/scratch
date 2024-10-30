#!/bin/bash

# 检查是否提供了参数
if [ -z "$1" ]; then
    echo "用法: $0 <新主机名>"
    exit 1
fi

# 获取新主机名
NEW_HOSTNAME=$1

# 使用 hostnamectl 命令设置新的主机名
sudo hostnamectl set-hostname "$NEW_HOSTNAME" --static

# 更新 /etc/hosts 文件
sudo sed -i "s/127.0.1.1 .*/127.0.1.1 $NEW_HOSTNAME/" /etc/hosts

# 确认更改
echo "主机名已更改为: $NEW_HOSTNAME"
echo "当前主机名为: $(hostname)"

exit 0
