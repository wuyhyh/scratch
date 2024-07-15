在Linux内核中，与时间流逝有关的数据结构和函数广泛用于处理各种定时任务、超时事件和时间管理。以下是一些主要的数据结构和函数：

### 数据结构

1. **`jiffies`**
    - **定义**：一个全局变量，记录自系统启动以来的时钟周期数。
    - **用途**：用于内核中的定时和调度操作。

2. **`timer_list`**
    - **定义**：表示内核定时器的结构体。
    - **主要字段**：
        - `expires`：定时器到期的`jiffies`值。
        - `function`：定时器到期时调用的回调函数。
        - `data`：传递给回调函数的参数。
    - **用途**：实现基于`jiffies`的定时功能。

3. **`hrtimer`**
    - **定义**：高分辨率定时器的结构体。
    - **主要字段**：
        - `function`：定时器到期时调用的回调函数。
        - `expires`：定时器到期的时间点，以`ktime_t`表示。
    - **用途**：提供纳秒级精度的定时功能。

4. **`ktime_t`**
    - **定义**：用于表示高精度时间的结构体，通常以纳秒为单位。
    - **用途**：在高分辨率定时器和时间管理中使用。

5. **`work_struct` 和 `delayed_work`**
    - **定义**：表示内核工作队列的结构体。
    - **主要字段**：
        - `work`：工作队列项。
        - `timer`：用于延时调度的定时器（`delayed_work`）。
    - **用途**：实现内核中的延时工作机制。

### 主要函数

1. **与 `jiffies` 相关的函数**
    - **`jiffies_to_msecs()`**：将`jiffies`转换为毫秒。
    - **`msecs_to_jiffies()`**：将毫秒转换为`jiffies`。
    - **`time_after()`**：比较两个`jiffies`值，判断一个时间是否在另一个时间之后。

2. **定时器相关函数**
    - **`init_timer()`**：初始化定时器。
    - **`add_timer()`**：添加定时器到定时器链表。
    - **`mod_timer()`**：修改定时器的超时时间。
    - **`del_timer()`**：删除定时器。

3. **高分辨率定时器相关函数**
    - **`hrtimer_init()`**：初始化高分辨率定时器。
    - **`hrtimer_start()`**：启动高分辨率定时器。
    - **`hrtimer_cancel()`**：取消高分辨率定时器。

4. **时间获取函数**
    - **`get_jiffies_64()`**：获取64位的`jiffies`值。
    - **`ktime_get()`**：获取当前时间，以`ktime_t`表示。
    - **`ktime_get_real()`**：获取当前的实时时间，以`ktime_t`表示。
    - **`getnstimeofday()`**：获取当前的实时时间，以`timespec`结构体表示，精度为纳秒。
    - **`do_gettimeofday()`**：获取当前的实时时间，以`timeval`结构体表示，精度为微秒。

5. **工作队列相关函数**
    - **`INIT_WORK()`**：初始化工作队列项。
    - **`schedule_work()`**：调度工作队列项立即执行。
    - **`INIT_DELAYED_WORK()`**：初始化延时工作队列项。
    - **`schedule_delayed_work()`**：调度延时工作队列项。

6. **时间延迟函数**
    - **`msleep()`**：使当前任务休眠指定的毫秒数。
    - **`udelay()`**：使当前任务延迟指定的微秒数。
    - **`ndelay()`**：使当前任务延迟指定的纳秒数。

### 示例代码

#### 使用 `timer_list` 实现定时器
```c
#include <linux/timer.h>
#include <linux/jiffies.h>

struct timer_list my_timer;

void my_timer_callback(struct timer_list *timer) {
    printk("Timer expired\n");
}

void setup_timer(void) {
    timer_setup(&my_timer, my_timer_callback, 0);
    mod_timer(&my_timer, jiffies + msecs_to_jiffies(1000)); // 1 second
}
```

#### 使用 `hrtimer` 实现高分辨率定时器
```c
#include <linux/hrtimer.h>
#include <linux/ktime.h>

struct hrtimer my_hrtimer;

enum hrtimer_restart my_hrtimer_callback(struct hrtimer *timer) {
    printk("High resolution timer expired\n");
    return HRTIMER_NORESTART;
}

void setup_hrtimer(void) {
    ktime_t kt = ktime_set(1, 0); // 1 second
    hrtimer_init(&my_hrtimer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
    my_hrtimer.function = my_hrtimer_callback;
    hrtimer_start(&my_hrtimer, kt, HRTIMER_MODE_REL);
}
```

#### 使用 `delayed_work` 实现延时工作
```c
#include <linux/workqueue.h>

struct delayed_work my_delayed_work;

void my_delayed_work_function(struct work_struct *work) {
    printk("Delayed work executed\n");
}

void setup_delayed_work(void) {
    INIT_DELAYED_WORK(&my_delayed_work, my_delayed_work_function);
    schedule_delayed_work(&my_delayed_work, msecs_to_jiffies(1000)); // 1 second
}
```

通过这些数据结构和函数，Linux内核能够高效地处理各种与时间相关的任务和事件，确保系统的稳定运行和及时响应。