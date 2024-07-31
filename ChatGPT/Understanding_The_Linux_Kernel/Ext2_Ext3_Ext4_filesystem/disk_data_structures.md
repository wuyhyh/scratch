EXT2、EXT3 和 EXT4 文件系统使用多种磁盘数据结构来管理和组织文件和目录。这些数据结构包括超级块、组描述符、inode、数据块、目录条目等。以下是这些文件系统的主要磁盘数据结构：

### 1. 超级块 (Superblock)
超级块是文件系统的控制信息块，存储有关文件系统整体结构和状态的信息。包括：
- 文件系统大小
- 块大小
- 块组大小
- 可用块和 inode 数量
- 文件系统状态（挂载状态、最近的检查时间等）

### 2. 块组描述符 (Block Group Descriptor)
块组描述符存储每个块组的元数据，每个块组描述符包含的信息包括：
- 块位图（Block Bitmap）的位置
- inode 位图（Inode Bitmap）的位置
- inode 表（Inode Table）的位置
- 块组中空闲块和空闲 inode 的数量

### 3. 块位图 (Block Bitmap)
块位图是一个位图，用于跟踪块组中哪些块是已使用的，哪些是空闲的。每个位对应一个数据块，0 表示空闲，1 表示已使用。

### 4. inode 位图 (Inode Bitmap)
inode 位图是一个位图，用于跟踪块组中哪些 inode 是已使用的，哪些是空闲的。每个位对应一个 inode，0 表示空闲，1 表示已使用。

### 5. inode 表 (Inode Table)
inode 表是一个数组，每个 inode 都是一个结构体，存储文件或目录的元数据。inode 包含的信息包括：
- 文件类型和权限
- 文件所有者和组
- 文件大小
- 文件的直接、间接、双重间接和三重间接数据块指针
- 文件的时间戳（创建、修改、访问时间）

### 6. 数据块 (Data Blocks)
数据块是文件数据的实际存储位置。文件的内容被存储在一个或多个数据块中，通过 inode 中的指针进行管理。

### 7. 目录条目 (Directory Entries)
目录条目存储在数据块中，描述目录中包含的文件和子目录。每个目录条目包含以下信息：
- 文件名
- 对应的 inode 号
- 目录条目长度
- 文件类型

### 8. 日志 (Journal, EXT3 和 EXT4)
EXT3 和 EXT4 文件系统引入了日志系统，日志是一个专用区域，用于记录文件系统的元数据操作。日志结构包括：
- 日志超级块
- 日志描述符块
- 日志数据块
- 日志提交块

### 9. 组描述符表 (Group Descriptor Table)
组描述符表位于超级块之后，包含所有块组描述符的信息。这些描述符指向相应块组中的块位图、inode 位图和 inode 表。

### 10. 扩展属性 (Extended Attributes, EXT3 和 EXT4)
扩展属性是附加在文件或目录上的元数据，用于存储标准 inode 结构中不包含的额外信息。它们可以用于访问控制列表（ACL）、用户定义的属性等。

这些数据结构共同工作，以高效地管理和组织文件系统中的文件和目录，确保数据的一致性和完整性。EXT3 和 EXT4 在 EXT2 的基础上引入了日志和其他改进，以提高文件系统的可靠性和性能。