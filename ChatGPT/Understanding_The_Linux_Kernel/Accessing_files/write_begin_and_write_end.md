在 Linux 内核中，`prepare_write` 和 `commit_write` 是在旧的内核版本中使用的两个文件系统接口，用于支持写操作的准备和提交。它们已经在现代内核中被 `write_begin` 和 `write_end` 所取代，但理解它们的工作机制仍然有助于理解文件写入过程。

### `prepare_write` 和 `commit_write` 的工作机制

#### `prepare_write`

`prepare_write` 函数用于在写入数据之前准备一个内存页面。它的主要任务是确保页面在写入数据前已经被正确地映射，并且相应的内存区域已经被锁定和准备好写入。

##### `prepare_write` 的简化示例代码：

```c
int prepare_write(struct file *file, struct page *page, unsigned from, unsigned to) {
    struct address_space *mapping = page->mapping;
    void *kaddr;

    // 映射页面
    kaddr = kmap(page);

    // 如果需要，可以在这里初始化页面的内容

    // 返回成功
    return 0;
}
```

#### `commit_write`

`commit_write` 函数在数据写入完成后调用，用于提交写入的结果。它的主要任务是更新页面的状态，标记页面为脏页，并在需要时更新文件的大小。

##### `commit_write` 的简化示例代码：

```c
int commit_write(struct file *file, struct page *page, unsigned from, unsigned to) {
    struct address_space *mapping = page->mapping;

    // 标记页面为脏页
    mark_page_accessed(page);
    set_page_dirty(page);

    // 更新文件大小
    if (to > mapping->host->i_size)
        i_size_write(mapping->host, to);

    // 解除页面映射
    kunmap(page);

    // 解锁页面
    unlock_page(page);

    // 返回成功
    return 0;
}
```

### `prepare_write` 和 `commit_write` 的调用流程

1. **页面准备**：在文件系统执行写操作时，会调用 `prepare_write` 函数。该函数确保页面已经被正确映射，并且可以安全地进行写入操作。
2. **数据写入**：数据被写入页面的内存区域。
3. **提交写入**：写入完成后，调用 `commit_write` 函数。该函数标记页面为脏页，并在需要时更新文件大小，最后解除页面映射并解锁页面。

### `write_begin` 和 `write_end` 的现代替代

现代 Linux 内核使用 `write_begin` 和 `write_end` 取代了 `prepare_write` 和 `commit_write`。它们提供了类似的功能，但接口更为通用和灵活。

#### `write_begin`

`write_begin` 函数在写入数据之前准备一个内存页面。它的主要任务是确保页面在写入数据前已经被正确地映射，并且相应的内存区域已经被锁定和准备好写入。

##### `write_begin` 的简化示例代码：

```c
int myfs_write_begin(struct file *file, struct address_space *mapping,
                     loff_t pos, unsigned len, unsigned flags,
                     struct page **pagep, void **fsdata) {
    pgoff_t index = pos >> PAGE_SHIFT;
    struct page *page;

    // 查找或分配页面
    page = grab_cache_page_write_begin(mapping, index);
    if (!page)
        return -ENOMEM;

    // 映射页面
    *pagep = page;
    return 0;
}
```

#### `write_end`

`write_end` 函数在数据写入完成后调用，用于提交写入的结果。它的主要任务是更新页面的状态，标记页面为脏页，并在需要时更新文件的大小。

##### `write_end` 的简化示例代码：

```c
int myfs_write_end(struct file *file, struct address_space *mapping,
                   loff_t pos, unsigned len, unsigned copied,
                   struct page *page, void *fsdata) {
    // 标记页面为脏页
    set_page_dirty(page);

    // 更新文件大小
    if (pos + copied > i_size_read(mapping->host))
        i_size_write(mapping->host, pos + copied);

    // 解锁页面
    unlock_page(page);
    put_page(page);

    return copied;
}
```

### `write_begin` 和 `write_end` 的调用流程

1. **页面准备**：在文件系统执行写操作时，会调用 `write_begin` 函数。该函数确保页面已经被正确映射，并且可以安全地进行写入操作。
2. **数据写入**：数据被写入页面的内存区域。
3. **提交写入**：写入完成后，调用 `write_end` 函数。该函数标记页面为脏页，并在需要时更新文件大小，最后解除页面映射并解锁页面。

### 总结

尽管 `prepare_write` 和 `commit_write` 在现代内核中已被替代，但它们的核心概念和功能在新的接口中得到了保留和扩展。理解这些接口有助于深入了解 Linux 文件系统的写操作机制。如果你对某个特定文件系统的实现或更详细的实现细节感兴趣，可以进一步探讨。