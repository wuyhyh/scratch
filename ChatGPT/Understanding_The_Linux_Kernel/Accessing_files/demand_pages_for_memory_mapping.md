内存映射中的请求调页（Demand Paging）是一种优化技术，用于提高内存使用效率和系统性能。请求调页的作用是延迟将数据从磁盘加载到内存的时间，只有在实际访问页面时才加载该页面。这种机制减少了内存的初始占用，提高了系统的响应速度。

### 请求调页的作用

1. **减少内存占用**：只有在访问页面时才加载页面，减少了不必要的内存占用。
2. **提高启动速度**：程序启动时不需要立即加载所有页面，只需加载必要的页面，从而提高启动速度。
3. **提高系统性能**：通过延迟加载页面，系统可以更高效地利用内存和 I/O 资源。

### 请求调页的实现

请求调页在操作系统中通过缺页异常（Page Fault）机制实现。当进程访问一个未加载的页面时，会触发缺页异常，操作系统捕获异常并加载相应的页面。

#### 内核中的实现过程

1. **页面表条目初始化**：在内存映射时，内核为映射区域创建页表条目，但这些条目初始化为无效状态，指示页面尚未加载。
2. **触发缺页异常**：当进程访问未加载的页面时，CPU 检测到页表条目无效，并触发缺页异常。
3. **处理缺页异常**：内核捕获缺页异常，并调用相应的缺页处理函数。
4. **加载页面**：缺页处理函数从磁盘加载页面到内存，并更新页表条目，使其指向新加载的页面。
5. **继续执行**：页面加载完成后，内核重新调度进程，继续执行引发缺页异常的指令。

#### 具体步骤示例

1. **初始化页表条目**

在调用 `mmap` 系统调用时，内核为映射区域创建虚拟内存区域（VMA）和页表条目，但这些条目指向一个共享的缺页处理函数。

```c
struct vm_area_struct *vma;
vma = kmem_cache_alloc(vm_area_cachep, GFP_KERNEL);
vma->vm_start = addr;
vma->vm_end = addr + length;
vma->vm_flags = prot;
vma->vm_file = file;
insert_vm_struct(mm, vma);
```

2. **触发缺页异常**

当进程第一次访问映射区域时，CPU 发现对应的页表条目无效，并触发缺页异常。

3. **处理缺页异常**

内核捕获缺页异常，并调用文件系统的 `fault` 方法，从文件中读取相应的页面。

```c
static int myfs_fault(struct vm_fault *vmf) {
    struct page *page;
    loff_t offset = vmf->pgoff << PAGE_SHIFT;

    // 从文件中读取页面
    page = read_mapping_page(mapping, vmf->pgoff, NULL);
    if (IS_ERR(page))
        return VM_FAULT_SIGBUS;

    // 将页面映射到进程的页表中
    vmf->page = page;
    return 0;
}
```

4. **加载页面**

`read_mapping_page` 函数从文件中读取页面，并将页面内容加载到内存。

```c
struct page *read_mapping_page(struct address_space *mapping, pgoff_t index, void *data) {
    struct page *page;
    
    // 分配一个新的页面
    page = alloc_page(GFP_KERNEL);
    if (!page)
        return ERR_PTR(-ENOMEM);
    
    // 从磁盘读取数据到页面
    if (mapping->a_ops->readpage) {
        int err = mapping->a_ops->readpage(NULL, page);
        if (err < 0) {
            __free_page(page);
            return ERR_PTR(err);
        }
    }
    
    // 返回页面
    return page;
}
```

5. **更新页表条目**

内核将页面加载到内存后，更新页表条目，使其指向新加载的页面，并设置有效标志。

```c
static int myfs_mmap_fault(struct vm_fault *vmf) {
    struct page *page;

    // 加载页面
    page = read_mapping_page(vmf->vma->vm_file->f_mapping, vmf->pgoff, NULL);
    if (IS_ERR(page))
        return VM_FAULT_SIGBUS;

    // 将页面映射到进程的页表中
    vmf->page = page;
    return 0;
}
```

6. **继续执行**

页面加载完成后，内核重新调度进程，继续执行引发缺页异常的指令。

### 总结

请求调页通过延迟页面加载，显著提高了内存使用效率和系统性能。它的实现依赖于缺页异常机制，内核通过捕获缺页异常并加载相应的页面来实现请求调页。这种机制在提高程序启动速度和减少内存占用方面具有显著效果，是现代操作系统内存管理的重要组成部分。