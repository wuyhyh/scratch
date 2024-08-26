`sysfs` 是Linux内核中的一个伪文件系统，用于在用户空间和内核空间之间进行信息和控制的交互。它主要用于暴露内核对象的属性（如`kobject`、`kset`、设备、驱动等），使得用户空间可以通过文件系统的接口来访问和控制内核中的数据结构。`sysfs`的底层操作包括以下几个关键部分：

### 1. **创建与销毁文件和目录**
- **`sysfs_create_file(struct kobject *kobj, const struct attribute *attr)`**: 在`sysfs`中为特定的`kobject`创建一个文件。这个文件对应于一个属性（`attribute`），用户可以通过读写这个文件来访问和修改对应的内核属性。
- **`sysfs_remove_file(struct kobject *kobj, const struct attribute *attr)`**: 删除`sysfs`中与特定`kobject`相关联的文件。
- **`sysfs_create_group(struct kobject *kobj, const struct attribute_group *grp)`**: 为一个`kobject`创建一个属性组（文件组），即一次性创建多个属性文件。
- **`sysfs_remove_group(struct kobject *kobj, const struct attribute_group *grp)`**: 删除一个`kobject`的属性组。

### 2. **读写操作**
- **`show` 和 `store` 方法**: 这是在`sysfs`文件中进行读写的回调函数。每个属性（`attribute`）都可以定义`show`（用于读取属性值）和`store`（用于写入属性值）的回调函数。`show`函数会被调用来读取属性的当前值，而`store`函数则会被调用来处理用户写入的值。
- **`sysfs_read_file` 和 `sysfs_write_file`**: `sysfs`底层会调用这些函数来处理文件的读写操作。这些操作会调用对应的`show`和`store`回调函数。

### 3. **属性的定义与注册**
- **`ATTRIBUTE(attr_name, mode, show, store)`**: 用于定义一个`sysfs`属性。这个宏会生成一个`attribute`结构体，该结构体包含了属性的名称、权限以及指向`show`和`store`函数的指针。
- **`kobj_attribute` 结构体**: 是一个包含了`kobject`指针的`attribute`结构体。通过它，可以方便地将`kobject`和`sysfs`文件系统中的属性关联起来。

### 4. **目录的创建与管理**
- **`sysfs_create_dir(struct kobject *kobj)`**: 为一个`kobject`在`sysfs`中创建一个目录。这个目录会与`kobject`关联，并且包含`kobject`的属性文件。
- **`sysfs_remove_dir(struct kobject *kobj)`**: 删除一个`kobject`在`sysfs`中的目录。

### 5. **符号链接**
- **`sysfs_create_link(struct kobject *kobj, struct kobject *target, const char *name)`**: 在`sysfs`中创建一个符号链接，链接到另一个`kobject`的目录。
- **`sysfs_remove_link(struct kobject *kobj, const char *name)`**: 删除`sysfs`中的一个符号链接。

### 6. **与用户空间的事件通知**
- **`sysfs_notify(struct kobject *kobj, const char *dir, const char *attr)`**: 当一个属性发生改变时，通过这个函数通知用户空间。这通常会触发`inotify`或`poll`等机制，使用户空间进程可以感知到`sysfs`中属性的变化。

### 7. **文件系统操作**
- **挂载和卸载**: `sysfs`通常挂载在 `/sys` 目录下，可以通过命令 `mount -t sysfs sysfs /sys` 来挂载，通过 `umount /sys` 来卸载。
- **文件系统类型注册**: `sysfs` 作为文件系统的一部分，通过 `register_filesystem` 函数注册到内核中。

### 8. **内核事件处理**
- **`uevent`**: `sysfs`可以触发`uevent`，将内核中的事件传递给用户空间。用户空间的`udevd`守护进程会捕获这些事件并执行相应的操作，如加载驱动模块。

这些底层操作共同作用，使得`sysfs`成为Linux内核和用户空间之间的重要桥梁，提供了一种统一、可编程的接口来访问和控制内核对象的状态和行为。