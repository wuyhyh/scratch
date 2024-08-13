在 Linux 系统中，`/proc` 文件系统中有多个文件可以用来查询系统中断的信息。以下是一些常用的文件及其内容：

### 1. `/proc/interrupts`
这个文件显示了当前系统中断的分布和统计信息，包括每个中断号的触发次数，以及每个CPU处理的中断数量。内容示例如下：

```
           CPU0       CPU1       CPU2       CPU3       
  0:         45          0          0          0   IO-APIC   2-edge      timer
  1:          2          0          0          0   IO-APIC   1-edge      i8042
  8:          0          0          0          0   IO-APIC   8-edge      rtc0
  9:          0          0          0          0   IO-APIC   9-fasteoi   acpi
 12:          5          0          0          0   IO-APIC  12-edge      i8042
 16:        347          0          0          0   IO-APIC  16-fasteoi   ehci_hcd:usb1, uhci_hcd:usb2
...
```

#### 主要字段：
- **IRQ number**: 中断号。
- **CPU columns**: 每个 CPU 核心处理该中断的次数。
- **Type**: 中断类型，如 `IO-APIC` 或 `PCI-MSI`。
- **Name**: 中断关联的设备或驱动程序的名称。

### 2. `/proc/stat`
这个文件包含了大量的系统统计信息，其中也包括中断相关的数据。文件内容的示例如下：

```
cpu  2255 34 2290 22625563 6290 127 456
intr 11444280 11319955 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
...
```

#### 相关字段：
- **intr**: 后面的数字表示自系统启动以来所有中断的累计计数。紧随其后的数列表示每个中断号的累计触发次数。

### 3. `/proc/irq/<IRQ_number>/`
这个目录下有一些文件提供了与特定中断号相关的详细信息。例如：

- **`/proc/irq/<IRQ_number>/smp_affinity`**：控制该中断在多处理器系统中分布到哪些CPU上。它通常是一个位掩码，表示允许哪些 CPU 处理该中断。
- **`/proc/irq/<IRQ_number>/affinity_hint`**：提示内核在处理中断时如何分配CPU，通常用于帮助中断负载均衡。
- **`/proc/irq/<IRQ_number>/spurious`**：显示与特定中断号相关的虚假中断（spurious interrupts）的统计信息。

### 4. `/proc/softirqs`
这个文件显示了软中断（soft IRQ）的统计信息，按 CPU 核心统计。文件内容示例如下：

```
                    CPU0       CPU1       CPU2       CPU3       
          HI:          0          0          0          0
       TIMER:     123456     123789     123456     123789
      NET_TX:          0          0          0          0
      NET_RX:          0          0          0          0
       BLOCK:          0          0          0          0
    IRQ_POLL:          0          0          0          0
     TASKLET:          0          0          0          0
       SCHED:          0          0          0          0
     HRTIMER:          0          0          0          0
         RCU:          0          0          0          0
```

#### 主要字段：
- **TIMER**: 软中断计数，由定时器触发。
- **NET_TX** / **NET_RX**: 网络传输/接收的软中断计数。

这些文件为系统管理员和开发人员提供了详细的中断信息，有助于诊断和优化系统性能。如果你需要更深入地理解某个文件的内容或格式，可以参考内核文档或查看具体的源代码。
