在 Linux 内核中，定时器（`timer`）是一种用于在未来特定时间点执行代码的机制。定时器广泛用于各种延时操作、超时检测等场景。以下是内核定时器的主要 API 以及它们的用途：

### 1. **struct timer_list**

首先，所有的定时器都基于 `struct timer_list` 结构体，这是定时器在内核中的基本数据结构。要使用内核定时器，首先需要定义并初始化一个 `timer_list` 结构体。

```c
struct timer_list my_timer;
```

### 2. **timer_setup()**

`timer_setup()` 用于初始化一个 `timer_list` 结构体，并指定定时器的回调函数。这个函数在内核 4.15 版本中引入，替代了较早的 `init_timer()` 和 `setup_timer()` 接口。

```c
void timer_setup(struct timer_list *timer, void (*function)(struct timer_list *), unsigned int flags);
```

- **`timer`**: 指向 `timer_list` 结构体的指针。
- **`function`**: 定时器触发时要调用的回调函数。
- **`flags`**: 定时器的标志（通常为 0）。

示例：
```c
timer_setup(&my_timer, my_timer_callback, 0);
```

### 3. **add_timer()**

`add_timer()` 将初始化后的定时器加入到内核定时器列表中，使其开始计时。

```c
int add_timer(struct timer_list *timer);
```

- **`timer`**: 指向要添加的 `timer_list` 结构体的指针。

示例：
```c
add_timer(&my_timer);
```

### 4. **mod_timer()**

`mod_timer()` 用于修改一个已经激活的定时器的超时时间。如果定时器已经在内核的定时器列表中，它将重新设置定时器的到期时间。如果定时器未激活，它会将定时器添加到内核定时器列表中。

```c
int mod_timer(struct timer_list *timer, unsigned long expires);
```

- **`timer`**: 指向要修改的 `timer_list` 结构体的指针。
- **`expires`**: 定时器的新的超时时间，以 `jiffies` 为单位。

示例：
```c
mod_timer(&my_timer, jiffies + msecs_to_jiffies(1000));  // 设置 1 秒后触发
```

### 5. **del_timer() 和 del_timer_sync()**

- **`del_timer()`** 用于从内核定时器列表中删除一个定时器。这个函数返回定时器是否已经被删除。

  ```c
  int del_timer(struct timer_list *timer);
  ```

- **`del_timer_sync()`** 也是删除定时器，但它会等待正在执行的定时器回调函数完成后再返回，以确保不会有定时器回调函数在删除后继续运行。

  ```c
  int del_timer_sync(struct timer_list *timer);
  ```

示例：
```c
del_timer(&my_timer);        // 删除定时器，不等待回调函数完成
del_timer_sync(&my_timer);   // 删除定时器，并等待回调函数完成
```

### 6. **timer_pending()**

`timer_pending()` 用于检查定时器是否已经激活或正在等待触发。它可以用于判断一个定时器是否已经在内核定时器列表中。

```c
int timer_pending(const struct timer_list *timer);
```

- **返回值**: 如果定时器正在等待触发，则返回非零值；否则返回零。

示例：
```c
if (timer_pending(&my_timer)) {
    // 定时器正在等待触发
}
```

### 7. **init_timer_key() 和 setup_timer()**（已弃用）

这些函数是旧版内核中用于初始化定时器的 API，已经在新版内核中被 `timer_setup()` 替代。不推荐在现代内核开发中使用这些接口。

### 示例代码

以下是一个简单的内核定时器示例代码，展示如何使用上述 API：

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/timer.h>
#include <linux/jiffies.h>

struct timer_list my_timer;

void my_timer_callback(struct timer_list *timer)
{
    printk(KERN_INFO "Timer expired and callback executed.\n");
}

static int __init my_module_init(void)
{
    printk(KERN_INFO "Initializing module...\n");

    timer_setup(&my_timer, my_timer_callback, 0);

    // 设置定时器在 1 秒后触发
    mod_timer(&my_timer, jiffies + msecs_to_jiffies(1000));

    return 0;
}

static void __exit my_module_exit(void)
{
    printk(KERN_INFO "Exiting module...\n");
    del_timer_sync(&my_timer);  // 确保定时器在退出模块前已删除
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Kernel Timer Example");
MODULE_AUTHOR("Your Name");
```

### 总结

这些是 Linux 内核中使用定时器的主要 API。根据需要的功能和定时器的生命周期，选择适当的 API 进行使用。如果你需要进行短时间或长时间的延迟、异步处理、超时检测等，定时器都是非常有用的工具。如果有进一步的疑问或需要更详细的解释，随时提问！