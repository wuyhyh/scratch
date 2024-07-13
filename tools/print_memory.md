要编写一个C语言用户态函数来打印一段内存中的内容，可以使用指针遍历这段内存，并逐字节打印。以下是一个示例代码，展示了如何实现这个功能：

### 示例代码

```c
#include <stdio.h>
#include <stdint.h>

void print_memory(const void *addr, size_t length) {
    const uint8_t *byte_ptr = (const uint8_t *)addr;
    size_t i;

    for (i = 0; i < length; i++) {
        printf("%02x ", byte_ptr[i]);
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }
    if (length % 16 != 0) {
        printf("\n");
    }
}

int main() {
    // 示例数据
    int example_data[] = {0x12345678, 0x9abcdef0, 0xdeadbeef, 0xfeedface};

    // 打印内存内容
    print_memory(example_data, sizeof(example_data));

    return 0;
}
```

### 代码解释

1. **`print_memory`函数**：
    - **参数**：
        - `const void *addr`：内存的起始地址。
        - `size_t length`：内存的长度。
    - **功能**：
        - 将传入的内存地址转化为字节指针 (`uint8_t`类型)。
        - 使用一个循环遍历内存中的每个字节，并以十六进制格式打印出来。
        - 每打印16个字节后换行，使输出更易读。

2. **示例数据**：
    - 定义一个包含4个整数的数组 `example_data`，用于示例演示。

3. **在`main`函数中调用`print_memory`**：
    - 打印 `example_data` 的内存内容，参数为数组的起始地址和数组的长度。

### 编译和运行

1. **保存代码**：将上述代码保存为 `print_memory.c`。
2. **编译代码**：
   ```bash
   gcc -o print_memory print_memory.c
   ```
3. **运行程序**：
   ```bash
   ./print_memory
   ```

### 输出结果

运行程序后，将打印 `example_data` 数组的内存内容。例如：

```
78 56 34 12 f0 de bc 9a ef be ad de ce fa ed fe 
```

每个字节以两位十六进制格式打印，连续的字节以空格分隔，每16个字节后换行。如果长度不是16的倍数，最后一行也会换行。

这段代码可以适用于任何类型的内存内容，只需传入内存的起始地址和长度即可。