在 Linux 内核中，固定映射（fixed mapping）是一种用于将虚拟地址直接映射到特定物理地址的机制，通常用于映射内存映射设备寄存器、物理内存区域等。这种映射在内核启动时进行，且映射关系保持不变。固定映射通过 `fixmap` 机制实现，主要应用于内核空间的某些特定用途。

### 固定映射的实现原理

#### 固定映射区域

固定映射区域是一个预定义的虚拟地址范围，专门用于映射特定的物理地址。在 x86_64 架构中，固定映射区域通常定义在内核地址空间的高端，具体地址范围根据架构和内核配置有所不同。

#### 固定映射表（Fixed Mapping Table）

内核使用一个固定映射表来管理这些映射关系。固定映射表包含了一系列预定义的条目，每个条目对应一个特定用途的固定映射。

### 固定映射的创建和管理

#### 固定映射宏

Linux 内核中提供了一组宏，用于创建和管理固定映射。这些宏主要定义在 `arch/x86/include/asm/fixmap.h` 文件中。

- `set_fixmap(idx, phys)`：将固定映射表中的 `idx` 条目映射到物理地址 `phys`。
- `clear_fixmap(idx)`：清除固定映射表中的 `idx` 条目的映射。

#### 固定映射的使用示例

假设我们需要将一个设备寄存器的物理地址 `0xFEDC0000` 映射到固定映射区域中的一个虚拟地址。以下是一个示例代码片段：

```c
#include <asm/fixmap.h>

// 物理地址
#define DEVICE_REGISTER_PHYS_ADDR 0xFEDC0000

// 固定映射索引（具体索引根据内核配置）
#define FIXMAP_IDX FIX_KMAP_BEGIN

void setup_device_register_mapping(void) {
    // 设置固定映射
    set_fixmap(FIXMAP_IDX, DEVICE_REGISTER_PHYS_ADDR);

    // 获取固定映射虚拟地址
    void *device_register_virt_addr = (void *)fix_to_virt(FIXMAP_IDX);

    // 现在可以使用 device_register_virt_addr 访问设备寄存器
    printk("Device register mapped to virtual address: %p\n", device_register_virt_addr);
}
```

#### 固定映射的工作流程

1. **定义固定映射索引**：在 `arch/x86/include/asm/fixmap.h` 中，定义固定映射索引和对应的虚拟地址。
2. **设置固定映射**：使用 `set_fixmap` 宏将固定映射表中的条目映射到指定的物理地址。
3. **获取虚拟地址**：使用 `fix_to_virt` 宏将固定映射索引转换为虚拟地址，以便在内核代码中使用。

### 固定映射的优点

1. **高效访问**：通过固定映射，内核可以快速访问特定的物理地址，不需要每次访问时重新计算地址映射。
2. **安全性和稳定性**：固定映射区域的映射关系在内核启动时设置，并保持不变，减少了地址空间管理的复杂性。
3. **简化设备驱动开发**：固定映射机制简化了设备驱动程序中对硬件设备寄存器的访问。

### 固定映射的示例应用

固定映射常用于以下场景：

- **设备寄存器映射**：将设备的物理寄存器地址映射到固定的虚拟地址，便于内核访问。
- **系统内存映射**：映射一些关键的物理内存区域，例如 ACPI 表、BIOS 数据区等。
- **调试和诊断**：在内核调试和诊断中，固定映射可以用于访问特定的物理内存区域以进行检查和调试。

### 具体例子：APIC 映射

高级可编程中断控制器（APIC）是一个常见的固定映射实例。在 x86 架构中，APIC 的物理地址通常为 `0xFEE00000`。内核通过固定映射将这个地址映射到虚拟地址，以便于内核访问。

```c
#include <asm/fixmap.h>

#define APIC_PHYS_ADDR 0xFEE00000
#define FIX_APIC_IDX __fix_to_virt(FIX_APIC_BASE)

void setup_apic_mapping(void) {
    // 设置固定映射
    set_fixmap(FIX_APIC_IDX, APIC_PHYS_ADDR);

    // 获取APIC寄存器的虚拟地址
    void *apic_virt_addr = (void *)fix_to_virt(FIX_APIC_IDX);

    // 现在可以使用 apic_virt_addr 访问APIC寄存器
    printk("APIC register mapped to virtual address: %p\n", apic_virt_addr);
}
```

通过这种方式，Linux 内核能够高效、安全地访问关键的硬件资源。