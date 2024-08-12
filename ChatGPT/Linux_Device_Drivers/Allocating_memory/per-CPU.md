在 Linux 内核中，Per-CPU 变量是每个 CPU 都有自己独立的副本的变量。它们用于避免在多处理器环境下对共享数据的竞争，同时又能高效地利用各个 CPU 的缓存。Per-CPU 变量通常用于统计信息、缓存数据等无需跨 CPU 共享的场景。

### 1. **定义和声明 Per-CPU 变量**

要定义一个 Per-CPU 变量，你需要使用特定的宏和关键字：

- **静态分配的 Per-CPU 变量**
    - 使用 `DEFINE_PER_CPU` 宏定义一个静态的 Per-CPU 变量。
  ```c
  DEFINE_PER_CPU(int, my_percpu_var);
  ```

  这将在每个 CPU 上创建一个名为 `my_percpu_var` 的 `int` 类型变量。

- **动态分配的 Per-CPU 变量**
    - 如果你需要在运行时动态分配 Per-CPU 变量，可以使用 `alloc_percpu` 函数：
  ```c
  int __percpu *my_dynamic_percpu_var;
  
  my_dynamic_percpu_var = alloc_percpu(int);
  if (!my_dynamic_percpu_var)
      return -ENOMEM;
  ```

### 2. **访问 Per-CPU 变量**

访问 Per-CPU 变量时，你需要使用特定的宏来确保访问到当前 CPU 的变量副本：

- **访问静态 Per-CPU 变量**
    - 使用 `get_cpu_var` 和 `put_cpu_var` 宏：
  ```c
  int val;
  
  val = get_cpu_var(my_percpu_var);
  get_cpu_var(my_percpu_var) = val + 1;
  put_cpu_var(my_percpu_var);
  ```

    - 或者，使用 `this_cpu_read` 和 `this_cpu_write` 宏，这些宏不需要手动平衡 `get_cpu_var` 和 `put_cpu_var`：
  ```c
  int val;

  val = this_cpu_read(my_percpu_var);
  this_cpu_write(my_percpu_var, val + 1);
  ```

- **访问动态分配的 Per-CPU 变量**
    - 对于动态分配的 Per-CPU 变量，你可以使用 `per_cpu_ptr` 宏获取指向当前 CPU 副本的指针，然后进行操作：
  ```c
  int *ptr;

  ptr = per_cpu_ptr(my_dynamic_percpu_var, smp_processor_id());
  *ptr = *ptr + 1;
  ```

    - 同样可以使用 `this_cpu_ptr` 获取指向当前 CPU 变量副本的指针：
  ```c
  int *ptr;

  ptr = this_cpu_ptr(my_dynamic_percpu_var);
  *ptr = *ptr + 1;
  ```

### 3. **释放动态分配的 Per-CPU 变量**

当你不再需要动态分配的 Per-CPU 变量时，应使用 `free_percpu` 释放它们：
```c
free_percpu(my_dynamic_percpu_var);
```

### 4. **使用注意事项**

- **效率和性能**：Per-CPU 变量非常适合存储不需要在 CPU 之间共享的数据，减少了锁的使用，提升了性能。

- **跨 CPU 访问**：避免跨 CPU 访问 Per-CPU 变量，因为这会导致缓存失效并降低性能。如果需要跨 CPU 访问，通常需要使用其他同步机制，如锁。

- **NUMA 环境**：在 NUMA（非统一内存访问）架构下，Per-CPU 变量通常也是本地的，这有助于减少远程内存访问的开销。

### 总结

Per-CPU 变量在 Linux 内核开发中非常有用，尤其是在多处理器环境中。通过静态或动态方式定义它们，然后使用专门的宏来访问每个 CPU 的副本，可以避免锁竞争，优化系统性能。在设计时，要考虑如何合理使用这些变量以最大限度地提高系统效率。
