在Linux内核的调度机制中，活动进程和过期进程的概念主要与时间片轮转调度（Round Robin）和完全公平调度器（CFS）相关联。以下是这些概念的实现细节：

### 活动进程和过期进程

1. **活动进程（Active Processes）**：
    - 这些是当前被系统调度器认为可以运行的进程，等待获取CPU时间片。
    - 活动进程队列包含所有尚未用完其时间片的进程。

2. **过期进程（Expired Processes）**：
    - 这些是已经用完其时间片，需要等待下一轮调度的进程。
    - 过期进程队列包含所有已经用完当前时间片的进程，这些进程需要等待调度器重新分配新的时间片。

### 实现机制

#### 时间片轮转调度（SCHED_RR）

在时间片轮转调度中，Linux内核通过两个队列来管理活动进程和过期进程：

- **活动队列（Active Queue）**：
    - 包含所有当前可运行且尚未用完时间片的进程。
    - 调度器从活动队列中选择下一个要运行的进程，并分配一个时间片给它。

- **过期队列（Expired Queue）**：
    - 包含所有用完时间片的进程。
    - 当一个进程用完其分配的时间片时，它被移动到过期队列。
    - 当活动队列中的进程全部用完时间片后，调度器交换活动队列和过期队列，开始新一轮的调度。

这种双队列机制确保了所有进程都能公平地获得CPU时间片，同时避免了某些进程长期占用CPU资源。

#### 完全公平调度器（CFS）

在CFS中，虽然没有明确的活动队列和过期队列的概念，但调度器通过虚拟运行时间（vruntime）来实现类似的功能：

- **虚拟运行时间（vruntime）**：
    - 每个进程都有一个虚拟运行时间，表示进程已经运行的时间与其优先级的加权和。
    - 进程的vruntime越小，优先级越高，越有可能被调度运行。

- **红黑树（Red-Black Tree）**：
    - CFS使用红黑树来管理所有可运行的进程，树中的每个节点代表一个进程。
    - 红黑树按进程的vruntime排序，左子树节点的vruntime比根节点小，右子树节点的vruntime比根节点大。
    - 调度器总是选择vruntime最小的进程（树的最左节点）来运行。

- **动态调整**：
    - 当一个进程用完其时间片后，调度器会更新其vruntime，并将其重新插入红黑树。
    - 这样，vruntime较大的进程（类似过期进程）会被推到树的右边，等待下次调度时再被选择运行。

### 总结

- **时间片轮转调度**：
    - 使用活动队列和过期队列。
    - 活动队列包含当前可运行的进程，过期队列包含用完时间片的进程。
    - 当活动队列为空时，交换活动队列和过期队列。

- **完全公平调度器**：
    - 使用红黑树管理进程。
    - 按vruntime排序进程，选择vruntime最小的进程运行。
    - 动态调整进程的vruntime，实现公平调度。

通过这些机制，Linux内核能够有效地管理和调度进程，确保系统资源的公平分配和高效利用。