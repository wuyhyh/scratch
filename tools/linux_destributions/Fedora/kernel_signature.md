以下是一个 Bash 脚本，用于配置内核签名并注册密钥以支持 Secure Boot。这个脚本将生成签名密钥，签名内核，并导入密钥到机器所有者密钥（MOK）列表中。

```bash
#!/bin/bash

# 检查是否有 root 权限
if [ "$EUID" -ne 0 ]; then
  echo "请以 root 用户运行此脚本。"
  exit 1
fi

# 安装必要的软件包
echo "安装 sbsigntools..."
sudo dnf install -y sbsigntools

# 生成签名密钥
echo "生成签名密钥..."
openssl req -new -x509 -newkey rsa:2048 -keyout MOK.key -out MOK.crt -nodes -days 3650 -subj "/CN=Custom Kernel/"

# 列出可用的内核
echo "当前可用的内核："
ls /boot/vmlinuz*

# 提示用户输入内核版本
read -p "请输入要签名的内核版本（例如：6.6.43）： " kernel_version

# 检查内核文件是否存在
kernel_path="/boot/vmlinuz-$kernel_version"
if [ ! -f "$kernel_path" ]; then
  echo "错误：内核文件 $kernel_path 不存在。"
  exit 1
fi

# 签名内核
echo "签名内核..."
sbsign --key MOK.key --cert MOK.crt "$kernel_path" -o "$kernel_path.signed"

# 替换原始内核文件
mv "$kernel_path.signed" "$kernel_path"

# 注册密钥
echo "注册 MOK 密钥..."
sudo mokutil --import MOK.crt

# 提示用户重启以完成密钥注册
echo "请记住刚才设置的密码，然后重启系统以完成 MOK 密钥注册。"
echo "完成注册后，请重新生成 GRUB 配置。"
echo "要重新生成 GRUB 配置，请运行以下命令："
echo "sudo grub2-mkconfig -o /boot/grub2/grub.cfg"
echo "对于 EFI 系统，使用以下命令："
echo "sudo grub2-mkconfig -o /boot/efi/EFI/fedora/grub.cfg"

# 提示用户重启
read -p "是否现在重启系统？ (y/n): " reboot_now
if [[ "$reboot_now" =~ ^[Yy]$ ]]; then
  sudo reboot
fi
```

### 使用说明

1. **保存脚本**：将上述脚本保存为 `sign_kernel.sh`。

2. **赋予执行权限**：

    ```bash
    chmod +x sign_kernel.sh
    ```

3. **运行脚本**：

    ```bash
    sudo ./sign_kernel.sh
    ```

### 脚本工作原理

1. **安装 sbsigntools**：确保系统上安装了 `sbsigntools` 包。
2. **生成签名密钥**：生成 RSA 密钥对，用于签名内核。
3. **列出可用内核**：显示 `/boot` 目录中的内核文件，提示用户输入要签名的内核版本。
4. **签名内核**：使用生成的密钥对内核进行签名，并替换原始内核文件。
5. **注册密钥**：使用 `mokutil` 导入密钥，并提示用户重启系统以完成密钥注册。
6. **更新 GRUB 配置**：提示用户在完成密钥注册后重新生成 GRUB 配置。

通过这个脚本，你可以自动化内核签名和密钥注册过程，以支持 Secure Boot。如果有任何问题，请随时告诉我。