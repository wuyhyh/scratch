在 Linux 内核中，休眠（sleep）操作是非常常见的，特别是在需要等待某个事件发生或延迟一段时间时。与休眠有关的函数和宏有许多，以下是一些关键的宏和函数及其工作原理：

### 休眠宏和函数

1. **`msleep` / `msleep_interruptible`**
2. **`ssleep`**
3. **`udelay` / `ndelay`**
4. **`schedule_timeout` / `schedule_timeout_interruptible`**
5. **`wait_event` 系列**

### 详细说明

#### `msleep` / `msleep_interruptible`

`msleep` 和 `msleep_interruptible` 用于毫秒级的休眠。

```c
void msleep(unsigned int msecs);
unsigned long msleep_interruptible(unsigned int msecs);
```

- `msleep`：当前任务会被放入非可中断状态，直到指定的毫秒数过去。
- `msleep_interruptible`：当前任务会被放入可中断状态，直到指定的毫秒数过去或被信号打断。

#### `ssleep`

`ssleep` 用于秒级的休眠。

```c
void ssleep(unsigned int seconds);
```

- `ssleep`：当前任务会被放入非可中断状态，直到指定的秒数过去。

#### `udelay` / `ndelay`

`udelay` 和 `ndelay` 用于微秒级和纳秒级的忙等待（busy-wait）。

```c
void udelay(unsigned long usecs);
void ndelay(unsigned long nsecs);
```

- `udelay`：在忙等待中等待指定的微秒数。
- `ndelay`：在忙等待中等待指定的纳秒数。

#### `schedule_timeout` / `schedule_timeout_interruptible`

`schedule_timeout` 和 `schedule_timeout_interruptible` 用于内核调度超时。

```c
long schedule_timeout(long timeout);
long schedule_timeout_interruptible(long timeout);
```

- `schedule_timeout`：将当前任务设置为不可中断状态，并调度其他任务运行，直到指定的时钟节拍数过去。
- `schedule_timeout_interruptible`：将当前任务设置为可中断状态，并调度其他任务运行，直到指定的时钟节拍数过去或被信号打断。

#### `wait_event` 系列

`wait_event` 系列宏用于在某个条件满足之前阻塞任务。

```c
void wait_event(wait_queue_head_t wq, condition);
void wait_event_interruptible(wait_queue_head_t wq, condition);
void wait_event_timeout(wait_queue_head_t wq, condition, timeout);
void wait_event_interruptible_timeout(wait_queue_head_t wq, condition, timeout);
```

- `wait_event`：在等待队列 `wq` 上等待，直到条件 `condition` 为真。
- `wait_event_interruptible`：在等待队列 `wq` 上可中断地等待，直到条件 `condition` 为真或被信号打断。
- `wait_event_timeout`：在等待队列 `wq` 上等待，直到条件 `condition` 为真或超时。
- `wait_event_interruptible_timeout`：在等待队列 `wq` 上可中断地等待，直到条件 `condition` 为真、被信号打断或超时。

### 工作原理

这些休眠函数和宏的工作原理通常包括以下几个步骤：

1. **设置任务状态**：
    - 在休眠前，将当前任务的状态设置为 `TASK_INTERRUPTIBLE` 或 `TASK_UNINTERRUPTIBLE`，以指示内核任务的当前状态。

2. **添加到等待队列**：
    - 将当前任务添加到一个等待队列中，这样内核调度器在条件满足时可以唤醒它。

3. **调用调度器**：
    - 调用调度函数（如 `schedule()`），让出 CPU，使其他任务能够运行。

4. **唤醒机制**：
    - 当条件满足或时间到达时，内核调度器会将任务从等待队列中移除，并设置其状态为 `TASK_RUNNING`，然后任务继续执行。

### 示例代码

#### 使用 `msleep`

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/delay.h>

static int __init my_module_init(void) {
    printk(KERN_INFO "Module initialized\n");
    msleep(1000); // 休眠 1000 毫秒
    printk(KERN_INFO "Woke up after 1 second\n");
    return 0;
}

static void __exit my_module_exit(void) {
    printk(KERN_INFO "Module exited\n");
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple module demonstrating msleep");
```

#### 使用 `wait_event_interruptible`

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/wait.h>
#include <linux/kthread.h>

static DECLARE_WAIT_QUEUE_HEAD(my_wq);
static int condition = 0;

static int my_thread(void *data) {
    printk(KERN_INFO "Thread started\n");
    wait_event_interruptible(my_wq, condition != 0);
    printk(KERN_INFO "Condition met, thread exiting\n");
    return 0;
}

static int __init my_module_init(void) {
    struct task_struct *task;
    printk(KERN_INFO "Module initialized\n");
    task = kthread_run(my_thread, NULL, "my_thread");
    msleep(5000); // 模拟一些工作
    condition = 1;
    wake_up_interruptible(&my_wq);
    return 0;
}

static void __exit my_module_exit(void) {
    printk(KERN_INFO "Module exited\n");
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple module demonstrating wait_event_interruptible");
```

这些示例展示了如何在内核模块中使用休眠函数和宏。通过这些函数和宏，可以在内核模块中实现复杂的同步和等待逻辑。