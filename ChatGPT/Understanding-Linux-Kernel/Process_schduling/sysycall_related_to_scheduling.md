与调度相关的系统调用主要包括以下几种，这些系统调用允许用户和程序设置进程的调度策略、优先级以及获取进程的调度信息：

1. **sched_setscheduler**：
    - **功能**：设置进程的调度策略和优先级。
    - **原型**：`int sched_setscheduler(pid_t pid, int policy, const struct sched_param *param);`
    - **参数**：
        - `pid`：要设置调度策略的进程ID。如果为0，则表示当前进程。
        - `policy`：调度策略，如SCHED_OTHER、SCHED_FIFO、SCHED_RR、SCHED_BATCH。
        - `param`：指向包含优先级信息的结构体 `struct sched_param`。

2. **sched_getscheduler**：
    - **功能**：获取进程的当前调度策略。
    - **原型**：`int sched_getscheduler(pid_t pid);`
    - **参数**：
        - `pid`：要获取调度策略的进程ID。如果为0，则表示当前进程。
    - **返回值**：返回当前进程的调度策略。

3. **sched_setparam**：
    - **功能**：设置进程的调度优先级。
    - **原型**：`int sched_setparam(pid_t pid, const struct sched_param *param);`
    - **参数**：
        - `pid`：要设置优先级的进程ID。如果为0，则表示当前进程。
        - `param`：指向包含优先级信息的结构体 `struct sched_param`。

4. **sched_getparam**：
    - **功能**：获取进程的调度优先级。
    - **原型**：`int sched_getparam(pid_t pid, struct sched_param *param);`
    - **参数**：
        - `pid`：要获取优先级的进程ID。如果为0，则表示当前进程。
        - `param`：指向用来存储优先级信息的结构体 `struct sched_param`。

5. **sched_yield**：
    - **功能**：让出CPU，使当前进程进入就绪队列的末尾，允许其他进程运行。
    - **原型**：`int sched_yield(void);`

6. **sched_get_priority_max**：
    - **功能**：获取指定调度策略的最大优先级。
    - **原型**：`int sched_get_priority_max(int policy);`
    - **参数**：
        - `policy`：调度策略。

7. **sched_get_priority_min**：
    - **功能**：获取指定调度策略的最小优先级。
    - **原型**：`int sched_get_priority_min(int policy);`
    - **参数**：
        - `policy`：调度策略。

8. **sched_rr_get_interval**：
    - **功能**：获取进程的时间片长度（仅适用于SCHED_RR策略）。
    - **原型**：`int sched_rr_get_interval(pid_t pid, struct timespec *interval);`
    - **参数**：
        - `pid`：要获取时间片长度的进程ID。如果为0，则表示当前进程。
        - `interval`：指向用来存储时间片长度的 `struct timespec` 结构体。

这些系统调用提供了对进程调度策略和优先级的控制和查询功能，允许用户和程序对进程的执行行为进行细粒度的管理和优化。