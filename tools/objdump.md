`objdump` 是一个强大的工具，用于显示可执行文件、目标文件和库文件的详细信息。它可以显示文件的汇编代码、符号表、段信息等等。下面是一些常用的 `objdump` 命令及其示例。

### 1. 查看文件头信息
查看可执行文件的文件头信息，包括文件类型、机器架构等：
```sh
objdump -f <filename>
```
示例：
```sh
objdump -f minimal
```

### 2. 查看段信息
查看可执行文件的段信息，包括每个段的地址、大小等：
```sh
objdump -h <filename>
```
示例：
```sh
objdump -h minimal
```

### 3. 反汇编
将可执行文件或目标文件的机器码反汇编为汇编代码：
```sh
objdump -d <filename>
```
示例：
```sh
objdump -d minimal
```

### 4. 查看符号表
显示文件的符号表，包括全局和局部符号：
```sh
objdump -t <filename>
```
示例：
```sh
objdump -t minimal
```

### 5. 查看动态符号表
对于动态链接的可执行文件，查看其动态符号表：
```sh
objdump -T <filename>
```
示例：
```sh
objdump -T minimal
```

### 6. 查看所有信息
显示文件的所有详细信息，包括头信息、段信息、符号表、反汇编代码等：
```sh
objdump -x <filename>
```
示例：
```sh
objdump -x minimal
```

### 示例：使用 `objdump` 反汇编最小的可执行文件
假设我们已经按照前面的步骤生成了 `minimal` 可执行文件，现在我们使用 `objdump` 来反汇编它并查看内容：

```sh
objdump -d minimal
```

输出可能如下所示：
```
minimal:     file format elf64-x86-64


Disassembly of section .text:

0000000000400080 <_start>:
  400080:       b8 3c 00 00 00          mov    $0x3c,%eax
  400085:       31 ff                   xor    %edi,%edi
  400087:       0f 05                   syscall
```

### 说明
- `0000000000400080 <_start>`：这是 `_start` 标签的地址。
- `b8 3c 00 00 00  mov $0x3c,%eax`：这条指令将 `0x3c` (即 60) 加载到 `eax` 寄存器，对应 `exit` 系统调用。
- `31 ff  xor %edi,%edi`：这条指令将 `edi` 清零，对应退出状态码 0。
- `0f 05  syscall`：这条指令触发系统调用。

通过上述步骤和示例，可以很容易地使用 `objdump` 工具来分析和理解 Linux 可执行文件的内部结构。