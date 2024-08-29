在 Linux 网络设备驱动程序中，驱动程序需要实现一组主要的设备方法，这些方法通过 `net_device_ops` 结构体进行定义和关联。这些方法定义了网络设备的核心操作，如启动、停止、发送数据包等。下面介绍一些常见且关键的设备方法：

### 1. **`ndo_init` 和 `ndo_uninit`**
- **`int (*ndo_init)(struct net_device *dev)`**
    - 在设备初始化时调用。这个方法用于执行设备的初始化操作，如分配资源、设置默认参数等。
- **`void (*ndo_uninit)(struct net_device *dev)`**
    - 在设备注销时调用。用于清理 `ndo_init` 中分配的资源。

### 2. **`ndo_open`**
- **`int (*ndo_open)(struct net_device *dev)`**
    - 当设备被启动时调用（例如通过 `ifconfig up` 或 `ip link set up`）。通常在此方法中，驱动程序需要开启设备的中断，分配 DMA 缓冲区，启动设备硬件等。

### 3. **`ndo_stop`**
- **`int (*ndo_stop)(struct net_device *dev)`**
    - 当设备被停止时调用（例如通过 `ifconfig down` 或 `ip link set down`）。在此方法中，驱动程序需要释放资源，禁用中断，停止设备硬件等。

### 4. **`ndo_start_xmit`**
- **`netdev_tx_t (*ndo_start_xmit)(struct sk_buff *skb, struct net_device *dev)`**
    - 这是发送数据包的核心方法。当内核希望通过设备发送数据包时，会调用此方法。驱动程序通常会将数据包放入发送队列并启动硬件传输。
- **返回值**：
    - `NETDEV_TX_OK`: 传输成功，数据包已进入发送队列。
    - `NETDEV_TX_BUSY`: 传输失败，设备忙碌，数据包未能进入发送队列。

### 5. **`ndo_tx_timeout`**
- **`void (*ndo_tx_timeout)(struct net_device *dev)`**
    - 当设备发送数据包超时时调用。驱动程序可以在此方法中执行错误恢复操作，例如重置设备、重新初始化硬件等。

### 6. **`ndo_set_rx_mode`**
- **`void (*ndo_set_rx_mode)(struct net_device *dev)`**
    - 设置接收模式的方法。例如，设备可以被配置为接收所有数据包（混杂模式）或只接收特定的多播/单播数据包。在该方法中，驱动程序需要根据新的接收模式配置硬件。

### 7. **`ndo_validate_addr`**
- **`int (*ndo_validate_addr)(struct net_device *dev)`**
    - 验证网络设备地址（如 MAC 地址）的方法。驱动程序可以在此方法中检查地址是否符合设备的硬件要求。

### 8. **`ndo_change_mtu`**
- **`int (*ndo_change_mtu)(struct net_device *dev, int new_mtu)`**
    - 改变设备的最大传输单元（MTU）的方法。在此方法中，驱动程序需要根据新的 MTU 值重新配置硬件参数。

### 9. **`ndo_set_mac_address`**
- **`int (*ndo_set_mac_address)(struct net_device *dev, void *addr)`**
    - 设置设备 MAC 地址的方法。在此方法中，驱动程序需要将新的 MAC 地址写入设备的硬件寄存器。

### 10. **`ndo_do_ioctl`**
- **`int (*ndo_do_ioctl)(struct net_device *dev, struct ifreq *ifr, int cmd)`**
    - 处理用户空间 `ioctl` 请求的方法。驱动程序可以在此方法中实现特定的控制命令，如获取或设置设备的特定参数。

### 11. **`ndo_get_stats64`**
- **`void (*ndo_get_stats64)(struct net_device *dev, struct rtnl_link_stats64 *stats)`**
    - 获取设备统计信息的方法。驱动程序需要在此方法中填充设备的传输、接收数据包计数、错误计数等统计信息。

### 12. **`ndo_change_carrier`**
- **`void (*ndo_change_carrier)(struct net_device *dev, bool new_carrier)`**
    - 改变设备的连接状态（carrier）的方法。在此方法中，驱动程序可以启用或禁用设备的物理连接状态。

### 13. **`ndo_vlan_rx_add_vid` 和 `ndo_vlan_rx_kill_vid`**
- **`int (*ndo_vlan_rx_add_vid)(struct net_device *dev, __be16 proto, u16 vid)`**
    - **`int (*ndo_vlan_rx_kill_vid)(struct net_device *dev, __be16 proto, u16 vid)`**
    - 添加或移除 VLAN ID 的方法。在 VLAN 相关的操作中，驱动程序可以使用这些方法来配置 VLAN 标记的接收处理。

### 14. **`ndo_set_features`**
- **`int (*ndo_set_features)(struct net_device *dev, netdev_features_t features)`**
    - 设置设备特性的方法。驱动程序可以在此方法中启用或禁用某些硬件特性，如硬件校验和、分散聚集等。

### 15. **`ndo_set_rx_mode`**
- **`void (*ndo_set_rx_mode)(struct net_device *dev)`**
    - 设置接收模式（如混杂模式、多播模式）的函数。驱动程序在该函数中应该根据接收模式的变化重新配置硬件。

### 16. **`ndo_get_iflink`**
- **`int (*ndo_get_iflink)(const struct net_device *dev)`**
    - 返回设备的下层接口索引。如果设备没有下层接口，这个方法应返回设备自己的接口索引。

### 总结
在网络设备驱动程序的开发过程中，实现上述这些主要设备方法是至关重要的。这些方法定义了设备如何被启动、停止、发送和接收数据包，以及如何处理各种设备状态和配置。通过正确实现这些方法，驱动程序可以与 Linux 内核的网络子系统无缝集成，并为用户空间提供稳定、可靠的网络设备服务。
