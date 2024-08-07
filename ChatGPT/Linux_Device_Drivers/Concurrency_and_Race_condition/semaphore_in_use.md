在Linux内核中，信号量（semaphore）是一种用于同步和互斥的机制。信号量主要用于控制多个线程或进程对共享资源的访问。Linux内核提供了两种信号量：计数信号量（counting semaphore）和二进制信号量（binary semaphore，或称为互斥锁 mutex）。

### 计数信号量

计数信号量允许多个线程同时访问共享资源，计数信号量的值表示允许访问资源的线程数量。

#### 关键结构和函数

1. **结构体**：`struct semaphore`

   ```c
   struct semaphore {
       atomic_t count;
       spinlock_t lock;
       struct list_head wait_list;
   };
   ```

2. **初始化**：

   ```c
   void sema_init(struct semaphore *sem, int val);
   ```

   初始化信号量 `sem`，初始值为 `val`。

3. **下降操作（P操作）**：

   ```c
   void down(struct semaphore *sem);
   int down_interruptible(struct semaphore *sem);
   int down_trylock(struct semaphore *sem);
   ```

   `down` 操作会尝试将信号量的值减1。如果信号量值为0，则当前任务会被阻塞，直到信号量值大于0。`down_interruptible` 可以被信号打断，`down_trylock` 尝试下降信号量，如果失败则立即返回。

4. **上升操作（V操作）**：

   ```c
   void up(struct semaphore *sem);
   ```

   `up` 操作会将信号量的值加1，如果有被阻塞的任务，则唤醒其中一个。

### 二进制信号量（互斥锁）

二进制信号量是计数信号量的特例，值只能是0或1，主要用于实现互斥锁。

#### 关键结构和函数

1. **结构体**：`struct mutex`

   ```c
   struct mutex {
       atomic_t count;
       spinlock_t wait_lock;
       struct list_head wait_list;
       struct task_struct *owner;
   };
   ```

2. **初始化**：

   ```c
   void mutex_init(struct mutex *lock);
   ```

   初始化互斥锁 `lock`。

3. **锁定操作**：

   ```c
   void mutex_lock(struct mutex *lock);
   int mutex_lock_interruptible(struct mutex *lock);
   int mutex_trylock(struct mutex *lock);
   ```

   `mutex_lock` 会尝试获取锁，如果锁已被占用，则当前任务会被阻塞，直到锁可用。`mutex_lock_interruptible` 可以被信号打断，`mutex_trylock` 尝试获取锁，如果失败则立即返回。

4. **解锁操作**：

   ```c
   void mutex_unlock(struct mutex *lock);
   ```

   释放互斥锁 `lock`。

### 使用示例

```c
struct semaphore sem;
sema_init(&sem, 1); // 初始化信号量，初始值为1

down(&sem); // 获取信号量
// 访问共享资源
up(&sem); // 释放信号量
```

```c
struct mutex my_mutex;
mutex_init(&my_mutex); // 初始化互斥锁

mutex_lock(&my_mutex); // 获取锁
// 访问共享资源
mutex_unlock(&my_mutex); // 释放锁
```

这些函数和结构在内核中用于管理并发访问，以确保数据的一致性和防止竞态条件。信号量和互斥锁是内核中常用的同步原语，理解其实现和使用方法对于编写安全可靠的内核代码至关重要。