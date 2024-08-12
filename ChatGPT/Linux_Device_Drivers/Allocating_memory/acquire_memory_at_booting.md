在 Linux 操作系统引导时获取专用缓冲区可以通过以下几种方法实现，具体方法取决于你的具体需求和应用场景。

### 1. **使用内核参数预留内存区域**
- 在引导时，你可以通过内核参数预留一部分物理内存，以供后续使用。例如，通过 `memmap` 参数预留一个内存区域：
  ```
  memmap=64K$0x10000000
  ```
  这将在物理地址 `0x10000000` 开始的地方预留 64KB 的内存。你可以在内核模块或驱动程序中使用这段内存。

- 在内核代码或模块中，你可以使用 `ioremap()` 或 `ioremap_nocache()` 将这段内存映射到虚拟地址空间，以便访问：
  ```c
  void __iomem *reserved_mem;
  reserved_mem = ioremap(0x10000000, 0x10000); // 映射64KB的内存
  ```

### 2. **使用 `kmalloc` 或 `vmalloc` 在引导时分配内存**
- 你可以在引导过程中或在内核模块加载时使用 `kmalloc`（用于小于一页的内存分配）或 `vmalloc`（用于分配大块连续虚拟内存）来分配专用缓冲区：
  ```c
  void *buffer;
  buffer = kmalloc(size, GFP_KERNEL); // 分配物理连续的内存
  ```
  或者：
  ```c
  void *buffer;
  buffer = vmalloc(size); // 分配虚拟连续的内存
  ```

- 这种方法适用于不需要与硬件设备直接交互的缓冲区分配。

### 3. **使用内核预留的 DMA 缓冲区**
- 如果你的缓冲区需要用于 DMA 操作，可以在驱动中使用 DMA API 分配 DMA 缓冲区：
  ```c
  dma_addr_t dma_handle;
  void *buffer;
  buffer = dma_alloc_coherent(&pdev->dev, size, &dma_handle, GFP_KERNEL);
  ```
  这种方法分配的内存是物理连续的，并且适用于 DMA 操作。

### 4. **在设备树或ACPI中预留内存**
- 对于嵌入式系统，你可以在设备树中预留内存区域，然后在驱动程序中使用这些预留的内存：
  ```dts
  reserved-memory {
      #address-cells = <1>;
      #size-cells = <1>;
      ranges;

      reserved_buffer: buffer@10000000 {
          reg = <0x10000000 0x10000>;
      };
  };
  ```

- 在驱动程序中，你可以通过解析设备树来获取这个内存区域，并将其映射到虚拟地址空间。

### 5. **内核启动选项**
- 你还可以通过在引导加载器（如 GRUB）中传递自定义内核启动选项，提示内核或模块在启动时进行特定的内存分配。

### 总结
上述方法根据你需要预留的缓冲区用途和系统结构有所不同。如果你需要在引导时预留物理内存，使用 `memmap` 参数和 `ioremap` 可能是最直接的方法。如果你是在模块加载时需要动态分配内存，可以使用 `kmalloc`、`vmalloc` 或者 DMA 相关 API。

根据你的具体需求选择合适的策略，并在实现时考虑内存的对齐要求、性能和内存的使用效率。

`alloc_bootmem` 函数在现代 Linux 内核中已经被弃用，且在较新的内核版本中已经移除。`alloc_bootmem` 函数曾经用于在内核启动早期从 boot memory allocator（引导内存分配器）中分配内存。这种分配方式通常在系统初始化的非常早期阶段使用，当时大部分的内存管理子系统还未初始化。

### 取代 `alloc_bootmem` 的方法

在新的内核版本中，`alloc_bootmem` 被 `memblock` API 所取代。`memblock` 是一个简单的物理内存管理器，能够在系统引导过程中管理和分配内存。

- **`memblock_alloc()`**: 分配一块内存
  ```c
  void *memblock_alloc(phys_addr_t size, phys_addr_t align);
  ```

- **`memblock_alloc_try_nid()`**: 尝试在特定 NUMA 节点上分配内存
  ```c
  void *memblock_alloc_try_nid(phys_addr_t size, phys_addr_t align, int nid);
  ```

- **`memblock_phys_alloc()`**: 分配物理地址的内存块
  ```c
  phys_addr_t memblock_phys_alloc(phys_addr_t size, phys_addr_t align);
  ```

这些 `memblock` 函数在内核初始化的早期阶段使用，可以替代 `alloc_bootmem` 来分配所需的内存块。由于它们是专门为早期引导阶段设计的，因此非常适合在内存管理子系统初始化之前使用。

### 示例

使用 `memblock_alloc()` 分配一个缓冲区的示例代码如下：

```c
#include <linux/memblock.h>

void __init my_early_init(void)
{
    void *buffer;

    buffer = memblock_alloc(1024, PAGE_SIZE);  // 分配 1024 字节，页面对齐
    if (!buffer)
        panic("Failed to allocate buffer during early init.\n");

    // 这里可以使用分配的缓冲区
}
```

### 总结

在现代 Linux 内核开发中，建议使用 `memblock` API 代替已弃用的 `alloc_bootmem`。`memblock` 提供了更强大的内存管理功能，并且与当前的内核设计保持一致。
