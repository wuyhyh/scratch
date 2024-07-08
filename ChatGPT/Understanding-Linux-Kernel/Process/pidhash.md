在 Linux 内核中，为了高效地管理和查找进程描述符（task_struct），内核使用了一个哈希表，称为 PID 哈希表（pidhash 表）。PID 哈希表通过进程 ID (PID) 将进程描述符组织起来，以便快速查找、插入和删除进程信息。下面详细介绍其工作原理和实现。

### 1. 进程描述符 (task_struct)

每个进程在内核中都有一个进程描述符（task_struct），它包含了进程的各种信息，如状态、优先级、内存映射、文件描述符等。

### 2. PID 哈希表

#### 2.1 哈希函数

PID 哈希表通过一个哈希函数将 PID 映射到哈希表中的某个桶（bucket）。在 Linux 内核中，哈希函数通常是简单的对哈希表大小取模操作：

```c
#define pid_hashfn(x) (hash_long((unsigned long)x, pidhash_shift))
```

其中 `hash_long` 是一个通用的哈希函数，`pidhash_shift` 是哈希表的大小参数。

#### 2.2 哈希桶

哈希表中的每个桶是一个链表，链表中的每个节点对应一个进程描述符。链表的头指针存储在一个数组中，数组的大小是哈希表的大小。

### 3. 进程的插入和删除

#### 3.1 插入进程

当创建一个新进程时，内核会根据该进程的 PID 计算哈希值，然后将进程描述符插入到对应的哈希桶中：

```c
void attach_pid(struct task_struct *task, enum pid_type type, struct pid *pid)
{
    unsigned long flags;
    struct pid_link *link;
    struct hlist_head *head = pid_hash[pid_hashfn(pid->numbers[type].nr)];

    link = &task->pids[type];
    link->pid = pid;
    spin_lock_irqsave(&pidmap_lock, flags);
    hlist_add_head_rcu(&link->node, head);
    spin_unlock_irqrestore(&pidmap_lock, flags);
}
```

#### 3.2 删除进程

当进程终止时，内核会将其从哈希表中删除：

```c
void detach_pid(struct task_struct *task, enum pid_type type)
{
    unsigned long flags;
    struct pid_link *link;

    link = &task->pids[type];
    spin_lock_irqsave(&pidmap_lock, flags);
    hlist_del_rcu(&link->node);
    spin_unlock_irqrestore(&pidmap_lock, flags);
    link->pid = NULL;
}
```

### 4. 查找进程

通过 PID 哈希表查找进程描述符是一个高效的操作。内核根据 PID 计算哈希值，然后遍历对应哈希桶的链表，找到匹配的进程描述符：

```c
struct task_struct *find_task_by_vpid(pid_t nr)
{
    struct pid *pid;
    struct task_struct *task = NULL;

    rcu_read_lock();
    pid = find_vpid(nr);
    if (pid)
        task = pid_task(pid, PIDTYPE_PID);
    rcu_read_unlock();

    return task;
}
```

### 5. 数据结构

#### 5.1 哈希表定义

PID 哈希表和相关数据结构的定义通常在 `kernel/pid.c` 中：

```c
#define PIDHASH_SZ (1 << pidhash_shift)
static struct hlist_head pid_hash[PIDHASH_SZ] __cacheline_aligned_in_smp;
```

#### 5.2 链表节点

每个链表节点对应一个进程描述符，使用内核中的 `hlist_node` 结构：

```c
struct pid_link {
    struct hlist_node node;
    struct pid *pid;
};
```

### 6. 哈希表大小和性能

哈希表的大小是一个重要的参数，它影响查找和插入操作的性能。通常，哈希表大小是根据系统中的最大进程数来动态确定的。较大的哈希表可以减少哈希冲突，从而提高查找效率，但会消耗更多的内存。

### 示例代码

以下是一个简化的示例，展示了如何插入和查找进程描述符：

```c
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/spinlock.h>
#include <linux/rculist.h>

#define PIDHASH_SZ 1024
static struct hlist_head pid_hash[PIDHASH_SZ];
static DEFINE_SPINLOCK(pidmap_lock);

static inline unsigned long hash_pid(pid_t pid)
{
    return hash_long((unsigned long)pid, ilog2(PIDHASH_SZ));
}

void insert_task(struct task_struct *task)
{
    unsigned long flags;
    unsigned long hash = hash_pid(task->pid);
    spin_lock_irqsave(&pidmap_lock, flags);
    hlist_add_head_rcu(&task->pid_links[PIDTYPE_PID], &pid_hash[hash]);
    spin_unlock_irqrestore(&pidmap_lock, flags);
}

struct task_struct *find_task(pid_t pid)
{
    struct task_struct *task;
    struct hlist_node *node;
    unsigned long hash = hash_pid(pid);

    rcu_read_lock();
    hlist_for_each_entry_rcu(task, node, &pid_hash[hash], pid_links[PIDTYPE_PID]) {
        if (task->pid == pid) {
            rcu_read_unlock();
            return task;
        }
    }
    rcu_read_unlock();
    return NULL;
}
```

### 总结

PID 哈希表通过哈希函数和链表的组合，使得进程描述符的查找、插入和删除操作高效快速。这种机制在大规模进程管理中表现尤为出色，确保了系统的性能和可扩展性。