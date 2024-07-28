在 Linux 系统中，内存映射（Memory Mapping）可以分为共享内存映射（Shared Memory Mapping）和私有内存映射（Private Memory Mapping）。它们在行为和用途上有所不同，主要体现在对修改的处理和进程间的可见性上。

### 共享内存映射（Shared Memory Mapping）

#### 概念

共享内存映射通过 `mmap` 系统调用将文件的内容映射到进程的虚拟地址空间，并且对映射区域的修改会直接反映到文件中。多个进程可以共享同一个文件映射，进程间的修改是可见的。

#### 特点

1. **进程间共享**：多个进程可以映射同一个文件，并共享对映射区域的访问。
2. **修改同步**：对映射区域的修改会同步到文件，并且其他进程可以看到这些修改。
3. **文件同步**：当映射区域被修改时，内核会在适当的时机将修改内容写回到文件。

#### 使用场景

- **进程间通信**：多个进程需要共享数据，并通过共享内存进行通信。
- **文件映射**：将大文件映射到内存中，提高访问效率，并且需要保存对文件的修改。

#### 示例代码

```c
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
    int fd;
    char *map;
    const char *text = "Hello, Shared Memory Mapping!";
    
    // 打开文件
    fd = open("/path/to/file", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // 调整文件大小
    ftruncate(fd, 4096);

    // 将文件映射到内存
    map = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return 1;
    }

    // 通过内存映射写入数据
    memcpy(map, text, strlen(text));

    // 解除映射
    if (munmap(map, 4096) == -1) {
        perror("munmap");
    }

    // 关闭文件
    close(fd);
    return 0;
}
```

### 私有内存映射（Private Memory Mapping）

#### 概念

私有内存映射通过 `mmap` 系统调用将文件的内容映射到进程的虚拟地址空间，但是对映射区域的修改不会影响文件，且其他进程不可见。每个进程对私有映射区域的修改只对自己可见，并且修改不会写回到文件。

#### 特点

1. **修改不可见**：对映射区域的修改仅对当前进程可见，不会影响文件或其他进程。
2. **写时拷贝（Copy-on-Write）**：内核在首次写入时创建一个新的物理页，将原始页的内容拷贝到新页中，修改只对当前进程可见。
3. **文件不受影响**：修改不会写回到文件，文件内容保持不变。

#### 使用场景

- **临时数据修改**：需要临时修改文件内容，但不希望这些修改保存到文件中。
- **进程间隔离**：多个进程需要访问相同的文件，但希望独立修改内容，不影响其他进程。

#### 示例代码

```c
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
    int fd;
    char *map;
    const char *text = "Hello, Private Memory Mapping!";
    
    // 打开文件
    fd = open("/path/to/file", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // 调整文件大小
    ftruncate(fd, 4096);

    // 将文件映射到内存
    map = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (map == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return 1;
    }

    // 通过内存映射写入数据
    memcpy(map, text, strlen(text));

    // 解除映射
    if (munmap(map, 4096) == -1) {
        perror("munmap");
    }

    // 关闭文件
    close(fd);
    return 0;
}
```

### 比较

| 特性                  | 共享内存映射（MAP_SHARED） | 私有内存映射（MAP_PRIVATE） |
|-----------------------|---------------------------|----------------------------|
| 进程间修改可见性       | 可见                      | 不可见                     |
| 修改是否写回文件       | 是                        | 否                         |
| 写时拷贝机制           | 否                        | 是                         |
| 用途                  | 进程间通信、文件修改       | 临时数据修改、进程间隔离   |

### 总结

共享内存映射和私有内存映射各有其特定的用途和特点。选择哪种映射方式取决于具体的应用场景和需求。在需要进程间通信和数据共享时，使用共享内存映射；在需要独立修改数据且不影响其他进程和文件时，使用私有内存映射。通过理解这两种映射方式的不同，可以更好地设计和优化应用程序。