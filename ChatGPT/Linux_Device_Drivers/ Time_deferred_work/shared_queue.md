共享工作队列（Shared Workqueue）是 Linux 内核中的一种机制，设计的目的是为了在多个不同的任务之间共享系统资源，减少资源浪费，提升系统的整体性能。共享工作队列的核心设计目的是为了高效管理和调度工作任务，尤其是在多核系统中。

### 共享工作队列的设计目的

1. **资源共享**：共享工作队列允许多个工作任务共享同一个工作队列，从而减少为每个任务创建单独工作队列的资源开销。这在资源受限的系统中尤其有用。

2. **负载均衡**：共享工作队列通过在多个 CPU 上分配工作任务，帮助内核自动实现负载均衡。这可以防止某个 CPU 过载，而其他 CPU 空闲的问题。

3. **提高效率**：共享工作队列允许多个任务并发运行，从而提高了任务的处理效率。共享队列通过减少队列之间的上下文切换，进一步优化了系统性能。

4. **简化管理**：使用共享工作队列可以简化代码和系统管理。开发者不必为每个任务创建和管理单独的工作队列，这减少了管理开销和复杂性。

### 如何使用共享工作队列

共享工作队列的使用主要包括以下步骤：初始化工作结构、将工作提交到共享工作队列，以及根据需要取消或同步工作。

#### 1. 初始化工作结构

首先，需要定义并初始化一个 `struct work_struct` 结构体，这个结构体表示要提交到队列中的工作任务。

```c
#include <linux/workqueue.h>

struct work_struct my_work;

void my_work_function(struct work_struct *work);

INIT_WORK(&my_work, my_work_function);
```

`my_work_function` 是一个回调函数，表示工作队列调度执行时调用的函数。

#### 2. 提交工作到共享工作队列

在 Linux 内核中，默认工作队列（`system_wq`）是一个共享工作队列。可以通过 `schedule_work()` 函数将工作提交到这个共享工作队列中。

```c
schedule_work(&my_work);
```

#### 3. 延迟提交工作

可以通过 `schedule_delayed_work()` 函数将工作延迟一段时间后再提交到共享工作队列中。延迟时间以 `jiffies` 为单位。

```c
struct delayed_work my_delayed_work;

INIT_DELAYED_WORK(&my_delayed_work, my_work_function);

schedule_delayed_work(&my_delayed_work, delay_in_jiffies);
```

#### 4. 取消或同步工作

在某些情况下，可能需要取消已经提交的工作，特别是在模块卸载或不再需要执行任务时。可以使用以下函数：

- **取消普通工作**:

```c
cancel_work_sync(&my_work);
```

- **取消延迟工作**:

```c
cancel_delayed_work_sync(&my_delayed_work);
```

这些函数确保在工作被取消后，不会有任何回调函数在执行。

### 共享工作队列的示例

以下是一个使用共享工作队列的简单内核模块示例：

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/workqueue.h>

struct work_struct my_work;

void my_work_function(struct work_struct *work)
{
    printk(KERN_INFO "Shared Workqueue: Executing work function.\n");
}

static int __init my_module_init(void)
{
    printk(KERN_INFO "Initializing module and scheduling work.\n");

    INIT_WORK(&my_work, my_work_function);

    // 提交工作到共享工作队列
    schedule_work(&my_work);

    return 0;
}

static void __exit my_module_exit(void)
{
    printk(KERN_INFO "Exiting module and canceling work.\n");

    // 取消工作，确保其不再执行
    cancel_work_sync(&my_work);
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Shared Workqueue Example");
MODULE_AUTHOR("Your Name");
```

### 注意事项

1. **多核支持**：共享工作队列在多核系统中表现良好，允许多个任务在不同 CPU 上并发执行，利用系统的多核优势进行负载均衡。

2. **睡眠安全**：工作队列运行在进程上下文中，因此可以安全地调用可能导致睡眠的函数，这使得工作队列非常适合处理复杂的任务。

3. **任务取消**：确保在不再需要任务时取消工作，特别是在模块卸载时，避免任务在模块被卸载后仍在执行，导致潜在的系统错误。

4. **共享资源管理**：当多个模块或驱动程序共享同一个工作队列时，确保正确管理任务的调度和取消，以避免资源竞争或任务冲突。

共享工作队列是一个强大且灵活的工具，适合处理大量并发任务和需要复杂处理的任务。通过合理使用共享工作队列，可以有效提高系统的响应性和性能。如果有其他问题，或者需要更详细的解释，随时问我！
