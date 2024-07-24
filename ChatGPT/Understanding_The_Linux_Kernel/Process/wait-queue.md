在 Linux 内核中，等待队列（wait queues）是用来管理等待某个特定事件的进程集合的。等待队列机制为内核提供了一种有效的方法，使进程能够睡眠，直到某个条件（如 I/O 操作完成）满足，然后被唤醒继续执行。

### 等待队列的组成

等待队列主要由以下两部分组成：

1. **等待队列头（wait_queue_head_t）**：这是等待队列的头部，用于管理所有在该队列上等待的进程。
2. **等待队列项（wait_queue_entry_t）**：这是队列中的每个项，代表一个正在等待的进程。

### 等待队列数据结构

#### 1. 等待队列头

等待队列头用于管理一个等待队列，定义在 `include/linux/wait.h` 中：

```c
typedef struct __wait_queue_head {
    spinlock_t lock;
    struct list_head head;
} wait_queue_head_t;
```

- `lock`：用于保护等待队列的自旋锁。
- `head`：链表头，链表中的每个节点都是一个等待队列项。

#### 2. 等待队列项

等待队列项用于表示一个在等待队列上等待的进程，定义在 `include/linux/wait.h` 中：

```c
typedef struct __wait_queue {
    unsigned int flags;
    void *private;
    wait_queue_func_t func;
    struct list_head entry;
} wait_queue_entry_t;
```

- `flags`：标志位，表示等待队列项的属性。
- `private`：指向等待队列项所属的进程（task_struct）。
- `func`：回调函数，当该项被唤醒时调用。
- `entry`：链表节点，用于将该项加入等待队列头的链表中。

### 等待队列的操作

#### 1. 初始化等待队列头

使用 `init_waitqueue_head` 函数初始化等待队列头：

```c
wait_queue_head_t my_wait_queue;
init_waitqueue_head(&my_wait_queue);
```

#### 2. 添加进程到等待队列

使用 `wait_event` 和 `wait_event_interruptible` 等宏，将进程添加到等待队列并进入睡眠状态。例如，`wait_event_interruptible` 的使用：

```c
wait_event_interruptible(my_wait_queue, condition);
```

这个宏会将当前进程添加到 `my_wait_queue` 等待队列，并且只有当 `condition` 变为真时才会被唤醒。如果进程在等待过程中收到信号，它会被唤醒并返回 -ERESTARTSYS。

#### 3. 唤醒等待队列上的进程

使用 `wake_up` 和 `wake_up_interruptible` 等函数来唤醒在等待队列上的进程。例如：

```c
wake_up(&my_wait_queue);
```

这会唤醒在 `my_wait_queue` 上等待的所有进程。

### 等待队列的工作机制

1. **睡眠机制**

当一个进程需要等待某个条件时，它会调用 `wait_event` 或 `wait_event_interruptible` 等宏。宏内部会检查条件是否满足，如果不满足，就将当前进程添加到等待队列并进入睡眠状态。睡眠过程中，进程的状态被设置为 TASK_INTERRUPTIBLE 或 TASK_UNINTERRUPTIBLE，并且它被从可运行队列中移除。

2. **唤醒机制**

当某个事件发生时，内核会调用 `wake_up` 或 `wake_up_interruptible` 等函数来唤醒在等待队列上的进程。函数内部会遍历等待队列，调用每个等待队列项的回调函数，将进程从等待队列中移除，并将其状态设置为 TASK_RUNNING，从而将其重新加入可运行队列。

### 示例代码

下面是一个简单的示例，展示了如何使用等待队列在内核模块中进行进程同步：

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/kthread.h>

MODULE_LICENSE("GPL");

static wait_queue_head_t my_wait_queue;
static int condition = 0;
static struct task_struct *thread;

static int thread_func(void *data)
{
    printk(KERN_INFO "Thread started\n");

    wait_event_interruptible(my_wait_queue, condition != 0);

    printk(KERN_INFO "Thread awoken\n");

    return 0;
}

static int __init my_module_init(void)
{
    init_waitqueue_head(&my_wait_queue);

    thread = kthread_run(thread_func, NULL, "my_thread");

    printk(KERN_INFO "Module loaded\n");

    return 0;
}

static void __exit my_module_exit(void)
{
    condition = 1;
    wake_up_interruptible(&my_wait_queue);

    kthread_stop(thread);

    printk(KERN_INFO "Module unloaded\n");
}

module_init(my_module_init);
module_exit(my_module_exit);
```

在这个示例中：

1. 初始化等待队列 `my_wait_queue`。
2. 创建一个内核线程 `thread`，在线程中调用 `wait_event_interruptible` 等待 `condition` 变量变为非零。
3. 在模块卸载时，将 `condition` 变量设置为 1，并调用 `wake_up_interruptible` 唤醒线程。

通过这种方式，等待队列机制使得内核可以有效地管理和同步多个进程之间的操作。