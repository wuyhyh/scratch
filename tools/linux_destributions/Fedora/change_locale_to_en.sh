#!/bin/bash

# 设置语言为英文（美国）
LANG_CONF="/etc/locale.conf"
BASH_PROFILE="$HOME/.bash_profile"
BASHRC="$HOME/.bashrc"
GRUB_CONF="/etc/default/grub"

# 修改 /etc/locale.conf 文件
echo "修改 $LANG_CONF 文件..."
sudo bash -c "echo 'LANG=en_US.UTF-8' > $LANG_CONF"

# 修改 .bash_profile 文件
if [ -f "$BASH_PROFILE" ]; then
    echo "修改 $BASH_PROFILE 文件..."
    grep -q 'export LANG=en_US.UTF-8' "$BASH_PROFILE" || echo 'export LANG=en_US.UTF-8' >> "$BASH_PROFILE"
    grep -q 'export LC_ALL=en_US.UTF-8' "$BASH_PROFILE" || echo 'export LC_ALL=en_US.UTF-8' >> "$BASH_PROFILE"
else
    echo "$BASH_PROFILE 文件不存在，创建并添加语言设置..."
    echo 'export LANG=en_US.UTF-8' >> "$BASH_PROFILE"
    echo 'export LC_ALL=en_US.UTF-8' >> "$BASH_PROFILE"
fi

# 修改 .bashrc 文件
if [ -f "$BASHRC" ]; then
    echo "修改 $BASHRC 文件..."
    grep -q 'export LANG=en_US.UTF-8' "$BASHRC" || echo 'export LANG=en_US.UTF-8' >> "$BASHRC"
    grep -q 'export LC_ALL=en_US.UTF-8' "$BASHRC" || echo 'export LC_ALL=en_US.UTF-8' >> "$BASHRC"
else
    echo "$BASHRC 文件不存在，创建并添加语言设置..."
    echo 'export LANG=en_US.UTF-8' >> "$BASHRC"
    echo 'export LC_ALL=en_US.UTF-8' >> "$BASHRC"
fi

# 安装 en_US.UTF-8 语言包
echo "安装 en_US.UTF-8 语言包..."
sudo dnf install -y glibc-langpack-en

# 修改 /etc/default/grub 文件
echo "修改 $GRUB_CONF 文件..."
sudo sed -i 's/GRUB_CMDLINE_LINUX="/GRUB_CMDLINE_LINUX="LANG=en_US.UTF-8 /' $GRUB_CONF

# 更新 GRUB 配置
echo "更新 GRUB 配置..."
sudo grub2-mkconfig -o /boot/grub2/grub.cfg

# 重新生成语言环境
echo "重新生成语言环境..."
sudo localectl set-locale LANG=en_US.UTF-8

# 提示重启系统
echo "设置完成，请重启系统以应用更改。"

# 重启系统（可选）
# echo "正在重启系统..."
# sudo reboot