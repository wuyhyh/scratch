在Linux内核中，获取动态内存的方式有多种，主要包括以下几种：

1. **kmalloc/kzalloc/kcalloc**:
    - `kmalloc`：用于分配指定大小的物理连续内存，类似于用户态的 `malloc`。
    - `kzalloc`：类似于 `kmalloc`，但分配的内存会被初始化为零。
    - `kcalloc`：分配并初始化数组内存，类似于 `calloc`。

   ```c
   void *ptr = kmalloc(size, GFP_KERNEL);
   void *ptr_zero = kzalloc(size, GFP_KERNEL);
   void *ptr_array = kcalloc(n, size, GFP_KERNEL);
   ```

2. **vmalloc**:
    - `vmalloc`：用于分配虚拟连续但物理上不连续的内存，适用于较大块的内存需求。

   ```c
   void *vptr = vmalloc(size);
   ```

3. **get_free_pages**:
    - `get_free_pages`：分配一个或多个连续的页面（物理连续）。

   ```c
   unsigned long page = get_free_pages(GFP_KERNEL, order);
   ```

4. **kmem_cache_alloc**:
    - `kmem_cache_alloc`：使用slab分配器进行内存分配，适用于经常分配和释放的相同大小对象。

   ```c
   struct kmem_cache *cachep;
   void *object;

   cachep = kmem_cache_create("cache_name", size, align, SLAB_HWCACHE_ALIGN, NULL);
  