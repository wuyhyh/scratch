要编写一个Python脚本，从本地Windows PC远程登录到多个Windows PC，你可以使用第三方库如 `pyautogui` 和 `subprocess`。这些库将帮助你自动化远程桌面连接（RDP）的过程，并处理用户交互。

下面是一个示例脚本，展示如何使用 `subprocess` 启动 RDP 连接，并使用 `pyautogui` 输入登录凭据。

### 安装必要的库

首先，确保你已经安装了 `pyautogui` 库：

```sh
pip install pyautogui
```

### 创建Python脚本

以下是一个示例Python脚本：

```python
import subprocess
import pyautogui
import time

def create_rdp_file(ip, username, filename):
    rdp_content = f"""
    screen mode id:i:2
    use multimon:i:0
    desktopwidth:i:1280
    desktopheight:i:720
    session bpp:i:32
    winposstr:s:0,1,200,200,1440,900
    full address:s:{ip}
    compression:i:1
    keyboardhook:i:2
    audiocapturemode:i:0
    videoplaybackmode:i:1
    connection type:i:2
    networkautodetect:i:1
    bandwidthautodetect:i:1
    displayconnectionbar:i:1
    username:s:{username}
    enableworkspacereconnect:i:0
    disable wallpaper:i:1
    allow font smoothing:i:0
    allow desktop composition:i:0
    disable full window drag:i:1
    disable menu anims:i:1
    disable themes:i:0
    disable cursor setting:i:0
    bitmapcachepersistenable:i:1
    drivestoredirect:s:
    """
    with open(filename, 'w') as file:
        file.write(rdp_content)

def connect_to_rdp(ip, username, password):
    rdp_file = f"{ip}.rdp"
    create_rdp_file(ip, username, rdp_file)
    
    # Launch RDP connection
    subprocess.Popen(['mstsc', rdp_file])
    
    # Wait for the RDP window to appear
    time.sleep(5)
    
    # Automatically enter the password
    pyautogui.typewrite(password)
    pyautogui.press('enter')

if __name__ == "__main__":
    targets = [
        {"ip": "192.168.1.101", "username": "user1", "password": "password1"},
        {"ip": "192.168.1.102", "username": "user2", "password": "password2"},
        # Add more targets as needed
    ]
    
    for target in targets:
        connect_to_rdp(target['ip'], target['username'], target['password'])
        # Wait a bit before connecting to the next PC
        time.sleep(10)
```

### 说明

1. **`create_rdp_file` 函数**：
    - 创建一个RDP文件，包含远程连接所需的参数。
    - 参数包括目标IP地址和用户名。

2. **`connect_to_rdp` 函数**：
    - 使用 `subprocess` 启动远程桌面连接，指定生成的RDP文件。
    - 使用 `pyautogui` 自动输入密码并按下“Enter”键。

3. **`targets` 列表**：
    - 包含多个目标PC的IP地址、用户名和密码。
    - 根据需要添加或修改目标PC信息。

### 运行脚本

确保你以管理员权限运行Python脚本，并且已安装所有必要的库。运行脚本时，它将自动创建RDP文件，启动远程桌面连接，并输入密码以完成登录。

### 注意事项

- 这个脚本假设所有远程桌面连接的初始配置是相同的。如果不同，可以调整RDP文件内容。
- `pyautogui` 自动化登录的过程可能不完全可靠，特别是如果网络延迟或窗口弹出速度不一致。可以根据需要调整 `time.sleep()` 的时长。
- 为了安全起见，避免在脚本中硬编码密码。可以考虑从安全存储中读取密码或使用其他安全方法管理凭据。

这个示例提供了一个基础框架，可能需要根据你的具体需求进行调整和扩展。