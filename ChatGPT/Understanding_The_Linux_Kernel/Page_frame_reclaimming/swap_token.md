在 Linux 内核的页框回收过程中，交换标记（swap flags）是用于管理和标识页面交换状态的重要机制。这些标记帮助内核在内存紧缺时决定如何处理和回收内存页面。以下是一些常见的交换标记及其用途：

### 常见的交换标记

1. **PG_swapbacked**:
    - 标记页面是否为交换支持页面（swap-backed page）。这种页面通常是匿名页面或共享内存页面，且可以被交换到交换区（swap space）。

2. **PG_swapcache**:
    - 标记页面是否为交换缓存页面（swap cache page）。交换缓存页面是指已经被交换出去但仍然保留在内存中的页面，以便在需要时快速恢复。

3. **PG_locked**:
    - 标记页面是否被锁定，防止其被交换或回收。某些关键数据页面会被锁定以确保其在内存中的存在。

4. **PG_referenced**:
    - 标记页面是否最近被引用，用于页面老化算法中的引用计数。这个标记帮助内核决定页面是否应该被交换或回收。

5. **PG_dirty**:
    - 标记页面是否被修改但尚未写回到磁盘。这类页面在回收前需要先写回到磁盘或交换区。

6. **PG_writeback**:
    - 标记页面是否正在被写回到磁盘或交换区。避免同时进行多次写回操作。

### 交换标记的使用

在页框回收过程中，内核通过这些交换标记来管理页面的状态和行为。下面是一些使用交换标记的关键步骤和代码示例：

1. **页面回收准备**:
    - 在回收页面之前，内核会检查页面的状态，判断其是否可以被交换或回收。

   ```c
   static unsigned long shrink_page_list(struct list_head *page_list,
                                         struct pglist_data *pgdat,
                                         struct scan_control *sc)
   {
       struct page *page;
       list_for_each_entry_safe(page, next, page_list, lru) {
           // 检查页面是否被锁定
           if (PageLocked(page)) {
               list_move(&page->lru, &pgdat->lru[LRU_ACTIVE]);
               continue;
           }

           // 检查页面是否脏
           if (PageDirty(page)) {
               // 写回页面
               writepage(page, sc);
               continue;
           }

           // 其他检查和处理...
       }
   }
   ```

2. **页面写回**:
    - 对于脏页面，内核会先将其写回到磁盘或交换区，然后再进行回收。

   ```c
   static int writepage(struct page *page, struct scan_control *sc)
   {
       // 标记页面正在写回
       SetPageWriteback(page);
       // 执行实际的写回操作
       return write_page_to_disk_or_swap(page);
   }
   ```

3. **页面交换**:
    - 对于交换支持页面，内核会将其数据写入交换区，并将页面标记为交换缓存页面。

   ```c
   static int swap_page(struct page *page, struct scan_control *sc)
   {
       // 将页面写入交换区
       swap_out_page(page);
       // 标记页面为交换缓存页面
       SetPageSwapCache(page);
   }
   ```

### 内核中的相关函数

1. **PageLocked**:
    - 检查页面是否被锁定。

   ```c
   static inline int PageLocked(struct page *page)
   {
       return test_bit(PG_locked, &page->flags);
   }
   ```

2. **PageDirty**:
    - 检查页面是否脏。

   ```c
   static inline int PageDirty(struct page *page)
   {
       return test_bit(PG_dirty, &page->flags);
   }
   ```

3. **SetPageWriteback**:
    - 将页面标记为正在写回。

   ```c
   static inline void SetPageWriteback(struct page *page)
   {
       set_bit(PG_writeback, &page->flags);
   }
   ```

4. **SetPageSwapCache**:
    - 将页面标记为交换缓存页面。

   ```c
   static inline void SetPageSwapCache(struct page *page)
   {
       set_bit(PG_swapcache, &page->flags);
   }
   ```

### 总结

Linux 内核通过使用一系列的交换标记来管理和优化页框回收过程。这些标记帮助内核跟踪页面的状态，决定哪些页面可以被交换或回收，从而确保系统内存的高效使用和稳定运行。如果你还有其他问题或需要更详细的解释，请随时告诉我。