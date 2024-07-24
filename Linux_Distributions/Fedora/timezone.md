## 配置fedora server的时区

在 Fedora Server 中更改时区可以通过以下几个步骤完成。你可以使用 `timedatectl` 命令来管理系统的时间设置。

### 步骤一：查看当前时区

首先，可以使用以下命令查看当前的时区设置：

```sh
timedatectl
```

输出示例：

```sh
Local time: Wed 2024-06-16 12:00:00 UTC
Universal time: Wed 2024-06-16 12:00:00 UTC
RTC time: Wed 2024-06-16 12:00:00
Time zone: UTC (UTC, +0000)
System clock synchronized: yes
NTP service: active
RTC in local TZ: no
```

### 步骤二：列出所有可用的时区

要列出所有可用的时区，可以使用以下命令：

```sh
timedatectl list-timezones
```

这将显示一个包含所有可用时区的列表。你可以通过管道和 `grep` 命令来过滤和查找特定的时区。例如，要查找与 "Asia" 相关的时区，可以使用：

```sh
timedatectl list-timezones | grep Asia
```

### 步骤三：更改时区

使用 `timedatectl set-timezone` 命令来设置新的时区。例如，如果你想将时区更改为 "Asia/Shanghai"，可以使用以下命令：

```sh
sudo timedatectl set-timezone Asia/Shanghai
```

### 步骤四：验证更改

最后，使用 `timedatectl` 命令再次查看当前的时区设置，确保更改已生效：

```sh
timedatectl
```

输出示例：

```sh
Local time: Wed 2024-06-16 20:00:00 CST
Universal time: Wed 2024-06-16 12:00:00 UTC
RTC time: Wed 2024-06-16 12:00:00
Time zone: Asia/Shanghai (CST, +0800)
System clock synchronized: yes
NTP service: active
RTC in local TZ: no
```

### 总结

通过以上步骤，你可以轻松地更改 Fedora Server 的时区设置。使用 `timedatectl` 命令不仅方便而且强大，可以让你快速查看和修改系统时间设置。