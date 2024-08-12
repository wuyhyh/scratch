在Linux内核中，访问I/O内存（Memory-Mapped I/O, MMIO）涉及到一组专门的函数，这些函数用于映射物理内存到内核的虚拟地址空间，并进行读写操作。这些函数通常提供了适当的内存屏障，以确保访问顺序的正确性。以下是常用的访问I/O内存的函数：

### 内存映射和取消映射函数

1. **ioremap**
    - **功能**：将物理地址范围映射到内核的虚拟地址空间，使得内核可以访问这些物理地址。
    - **原型**：
      ```c
      void __iomem *ioremap(resource_size_t phys_addr, unsigned long size);
      ```
    - **示例**：
      ```c
      void __iomem *reg_base;
      reg_base = ioremap(0xF0000000, 0x1000);  // 将物理地址0xF0000000开始的1KB映射到内核虚拟地址空间
      ```

2. **ioremap_nocache**
    - **功能**：与`ioremap`类似，但确保映射的内存区域不被缓存。这对于那些需要及时反映设备状态变化的寄存器尤为重要。
    - **原型**：
      ```c
      void __iomem *ioremap_nocache(resource_size_t phys_addr, unsigned long size);
      ```

3. **iounmap**
    - **功能**：取消先前通过`ioremap`或`ioremap_nocache`映射的内存区域，释放虚拟地址空间。
    - **原型**：
      ```c
      void iounmap(void __iomem *addr);
      ```
    - **示例**：
      ```c
      iounmap(reg_base);  // 取消映射
      ```

### I/O内存读写函数

这些函数用于在映射的I/O内存区域中进行数据的读取和写入操作。它们会自动处理内存屏障，以确保操作的顺序性。

1. **读取函数**

    - `readb(addr)`：读取一个字节（8位）。
    - `readw(addr)`：读取一个字（16位）。
    - `readl(addr)`：读取一个双字（32位）。
    - `readq(addr)`：读取一个四字（64位，适用于64位系统）。

   **示例**：
   ```c
   uint32_t value;
   value = readl(reg_base + 0x04);  // 从映射的I/O内存偏移0x04处读取32位数据
   ```

2. **写入函数**

    - `writeb(value, addr)`：写入一个字节（8位）。
    - `writew(value, addr)`：写入一个字（16位）。
    - `writel(value, addr)`：写入一个双字（32位）。
    - `writeq(value, addr)`：写入一个四字（64位，适用于64位系统）。

   **示例**：
   ```c
   writel(0x12345678, reg_base + 0x08);  // 向映射的I/O内存偏移0x08处写入32位数据
   ```

### 字符串I/O操作函数

这些函数用于批量的I/O操作，通常用于处理连续的寄存器或内存区域。

1. **读操作**

    - `memset_io(addr, value, count)`：将`count`个`value`字节填充到映射的I/O内存区域。
    - `memcpy_fromio(buf, addr, count)`：从映射的I/O内存区域复制`count`个字节到缓冲区`buf`。

   **示例**：
   ```c
   memset_io(reg_base, 0, 256);  // 将映射的I/O内存区域前256字节设置为0
   ```

2. **写操作**

    - `memcpy_toio(addr, buf, count)`：将缓冲区`buf`中的`count`个字节复制到映射的I/O内存区域。

   **示例**：
   ```c
   memcpy_toio(reg_base, buffer, 256);  // 将缓冲区中的256字节数据写入映射的I/O内存区域
   ```

### 其他辅助函数

- **ioread8/16/32/64** 和 **iowrite8/16/32/64**：这些是专门为I/O内存操作设计的函数，用于读取和写入8位、16位、32位和64位数据。它们是`readb/readw/readl/readq`和`writeb/writew/writel/writeq`的别名。

- **ioread8_rep/iowrite8_rep**：用于批量读取或写入数据的函数，这些函数在处理大块数据传输时效率较高。

### 总结

I/O内存访问函数为驱动程序开发者提供了一套强大的工具，用于与硬件设备进行低级别的内存映射I/O通信。这些函数涵盖了从内存映射到具体的数据读写操作，并且考虑了跨平台的一致性和性能优化。在实际开发中，根据设备的特性选择合适的函数可以确保系统的稳定性和效率。
