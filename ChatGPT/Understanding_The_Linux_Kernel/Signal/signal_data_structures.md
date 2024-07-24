在 Linux 内核中，信号处理涉及多个关键数据结构。这些数据结构在进程管理和信号处理的不同方面发挥作用。下面是一些主要的信号处理相关的数据结构及其详细解释：

### 1. `task_struct`
`task_struct` 是每个进程在内核中的表示，包含了与该进程相关的所有信息，包括信号处理的信息。它定义在 `include/linux/sched.h` 中。与信号处理相关的字段包括：

- `struct signal_struct *signal`：指向信号描述符的指针，包含与整个进程组相关的信号信息。
- `struct sighand_struct *sighand`：指向信号处理程序的指针，包含信号处理程序的指针和相关信息。
- `sigset_t pending`：存储未决信号的位图。
- `sigset_t blocked`：存储阻塞信号的位图。

### 2. `signal_struct`
`signal_struct` 结构体表示一个进程组的信号信息，定义在 `include/linux/sched/signal.h` 中。字段包括：

- `atomic_t count`：引用计数。
- `struct sigpending shared_pending`：存储进程组的共享未决信号队列。
- `struct task_struct *curr_target`：指向当前处理信号的任务。
- `sigset_t signal`：未决信号的位图。

### 3. `sighand_struct`
`sighand_struct` 结构体表示进程的信号处理程序信息，定义在 `include/linux/sched/signal.h` 中。字段包括：

- `refcount_t count`：引用计数。
- `spinlock_t siglock`：保护信号处理程序的自旋锁。
- `struct k_sigaction action[_NSIG]`：存储信号处理程序的数组，每个信号对应一个处理程序。

### 4. `sigpending`
`sigpending` 结构体存储未决信号的信息，定义在 `include/linux/sched/signal.h` 中。字段包括：

- `struct list_head list`：未决信号的链表。
- `sigset_t signal`：未决信号的位图。

### 5. `k_sigaction`
`k_sigaction` 结构体表示每个信号的处理程序，定义在 `include/linux/signal.h` 中。字段包括：

- `struct sigaction sa`：实际的信号处理程序，包含处理程序的地址、信号掩码等。
- `void (*handler)(int)`：信号处理函数。

### 6. `siginfo_t`
`siginfo_t` 结构体包含关于信号的详细信息，定义在 `include/uapi/asm-generic/siginfo.h` 中。字段包括：

- `int si_signo`：信号编号。
- `int si_errno`：与信号相关的错误编号。
- `int si_code`：信号的代码，指示信号的来源。
- 联合体 `si_value`：附加数据，可以是整数、指针等。

### 信号处理流程中的数据结构交互
1. **发送信号**：
    - 调用 `send_signal()` 函数，首先检查目标进程的 `task_struct` 中的 `blocked` 位图，决定是否将信号放入 `pending` 位图中。
    - 对于实时信号，信号会被放入 `sigqueue` 队列。

2. **接收信号**：
    - 进程返回用户态时，内核调用 `do_signal()` 检查 `pending` 信号位图和 `sigqueue` 队列。
    - 根据信号类型和处理策略，调用相应的处理程序。

3. **处理信号**：
    - `do_signal()` 中检查 `task_struct` 的 `sighand`，找到对应的信号处理程序（`k_sigaction`）。
    - 如果信号被捕获，则调用用户定义的处理程序；否则，使用默认处理程序。

### 示例代码
以下是一个简单的信号处理示例，演示了如何设置和处理信号：

```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle_sigint(int sig) {
    printf("Caught signal %d\n", sig);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = handle_sigint;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    printf("Press Ctrl+C to trigger SIGINT\n");
    while (1) {
        pause(); // 等待信号
    }

    return 0;
}
```

在这个示例中，`sigaction` 用于设置 SIGINT 的处理程序 `handle_sigint`。当用户按下 Ctrl+C 时，信号处理程序会被调用并输出捕获到的信号。

通过以上数据结构和信号处理流程的详细解释，希望能帮助你更好地理解 Linux 内核中的信号处理机制。如果有任何问题或需要进一步的解释，请随时告诉我！