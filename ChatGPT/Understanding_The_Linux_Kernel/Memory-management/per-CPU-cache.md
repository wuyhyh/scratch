在Linux内核中，per-CPU缓存（per-CPU cache）是一种优化机制，用于加速页框的分配和释放操作，减少竞争和锁争用，提高内存管理的效率。它主要通过在每个CPU上维护一个本地的页框缓存来实现。这种机制在伙伴系统（Buddy System）和slab分配器中都有应用。

### per-CPU缓存的作用

1. **减少锁争用**：
    - 每个CPU都有自己的缓存，不需要频繁地访问全局数据结构，减少了锁争用，提高了并行性能。

2. **提高缓存命中率**：
    - 内存分配和释放操作更可能在本地CPU上命中缓存，提高了内存操作的效率。

3. **降低延迟**：
    - 通过快速访问本地缓存，减少了内存分配和释放的延迟。

### per-CPU缓存的实现

#### 在伙伴系统中的实现

在伙伴系统中，per-CPU缓存主要用于页框的快速分配和释放。每个CPU维护一个局部缓存，用于存储最近分配或释放的页框。

**步骤**：

1. **初始化**：
    - 在系统启动时，每个CPU都会初始化自己的per-CPU缓存。

2. **页框分配**：
    - 当某个CPU需要分配页框时，首先尝试从本地per-CPU缓存中获取。如果本地缓存中有可用的页框，则直接返回。
    - 如果本地缓存中没有可用的页框，则从全局伙伴系统中分配页框，并将部分页框放入本地缓存，以备后续使用。

3. **页框释放**：
    - 当某个CPU释放页框时，首先尝试将页框放入本地per-CPU缓存。
    - 如果本地缓存已满，则将页框归还到全局伙伴系统中。

**示例代码**（简化版）：

```c
struct per_cpu_pages {
    int count;        // 当前缓存中的页框数量
    struct page *list; // 页框链表
};

struct per_cpu_pageset {
    struct per_cpu_pages pcp[2]; // 分别用于小页和大页
};

// 分配页框
struct page *alloc_pages(gfp_t gfp_mask, unsigned int order) {
    struct per_cpu_pages *pcp;
    struct page *page = NULL;

    // 获取当前CPU的per-CPU缓存
    pcp = &get_cpu_var(zone->pageset)->pcp[order];

    // 尝试从per-CPU缓存中获取页框
    if (pcp->count > 0) {
        page = pcp->list;
        pcp->list = page->next;
        pcp->count--;
    } else {
        // 从全局伙伴系统中分配页框
        page = __alloc_pages_nodemask(gfp_mask, order, NULL);
        // 将部分页框放入本地缓存
        refill_pcp_cache(pcp, order);
    }

    put_cpu_var(zone->pageset);
    return page;
}

// 释放页框
void free_pages(struct page *page, unsigned int order) {
    struct per_cpu_pages *pcp;

    // 获取当前CPU的per-CPU缓存
    pcp = &get_cpu_var(zone->pageset)->pcp[order];

    // 尝试将页框放入本地缓存
    if (pcp->count < pcp->high) {
        page->next = pcp->list;
        pcp->list = page;
        pcp->count++;
    } else {
        // 将页框归还到全局伙伴系统
        __free_pages_ok(page, order);
    }

    put_cpu_var(zone->pageset);
}
```

#### 在slab分配器中的实现

slab分配器也使用了per-CPU缓存来优化内存对象的分配和释放。每个CPU有一个slab缓存，用于存储最近分配或释放的内存对象。

**步骤**：

1. **初始化**：
    - 在系统启动时，每个CPU会为每种缓存对象类型初始化一个per-CPU缓存。

2. **对象分配**：
    - 当某个CPU需要分配内存对象时，首先尝试从本地per-CPU缓存中获取。如果本地缓存中有可用对象，则直接返回。
    - 如果本地缓存中没有可用对象，则从全局slab缓存中分配，并将部分对象放入本地缓存。

3. **对象释放**：
    - 当某个CPU释放内存对象时，首先尝试将对象放入本地per-CPU缓存。
    - 如果本地缓存已满，则将对象归还到全局slab缓存。

**示例代码**（简化版）：

```c
struct kmem_cache_cpu {
    void **freelist; // 本地空闲对象链表
    int nr_objs;     // 当前缓存中的对象数量
};

// 分配对象
void *kmem_cache_alloc(struct kmem_cache *cachep, gfp_t flags) {
    struct kmem_cache_cpu *c;
    void *obj = NULL;

    // 获取当前CPU的per-CPU缓存
    c = get_cpu_cache(cachep);

    // 尝试从per-CPU缓存中获取对象
    if (c->nr_objs > 0) {
        obj = c->freelist;
        c->freelist = *(void **)obj;
        c->nr_objs--;
    } else {
        // 从全局slab缓存中分配对象
        obj = slab_alloc(cachep, flags);
        // 将部分对象放入本地缓存
        refill_cpu_cache(c, cachep);
    }

    put_cpu_cache(cachep);
    return obj;
}

// 释放对象
void kmem_cache_free(struct kmem_cache *cachep, void *obj) {
    struct kmem_cache_cpu *c;

    // 获取当前CPU的per-CPU缓存
    c = get_cpu_cache(cachep);

    // 尝试将对象放入本地缓存
    if (c->nr_objs < c->limit) {
        *(void **)obj = c->freelist;
        c->freelist = obj;
        c->nr_objs++;
    } else {
        // 将对象归还到全局slab缓存
        slab_free(cachep, obj);
    }

    put_cpu_cache(cachep);
}
```

### 总结

per-CPU缓存是Linux内核中用于优化内存分配和释放的关键机制。通过在每个CPU上维护本地缓存，减少了对全局数据结构的访问和锁争用，提高了内存操作的效率。无论是伙伴系统还是slab分配器，per-CPU缓存都发挥了重要作用，确保系统在高并发和高负载下的性能和稳定性。

如果你有更多具体问题或需要更详细的解释，请继续提问。