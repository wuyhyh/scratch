在 Linux 内核中，捕获信号的过程包括设置信号处理程序、信号传递、信号捕获和处理。这一过程涉及多个系统调用和数据结构。下面详细解释捕获信号的过程。

### 1. 设置信号处理程序

在用户空间，进程可以通过 `signal()` 或 `sigaction()` 系统调用设置信号处理程序。

#### 使用 `signal()` 设置信号处理程序

```c
#include <signal.h>

void handler(int sig) {
    // 信号处理程序
}

int main() {
    signal(SIGINT, handler);
    while (1) {
        // 等待信号
    }
    return 0;
}
```

#### 使用 `sigaction()` 设置信号处理程序

`sigaction()` 提供了更强大的功能，包括设置信号掩码和其他选项。

```c
#include <signal.h>
#include <stdio.h>

void handler(int sig) {
    printf("Caught signal %d\n", sig);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    while (1) {
        // 等待信号
    }
    return 0;
}
```

### 2. 信号传递

当信号被发送到目标进程时，内核将信号添加到目标进程的未决信号队列中，并标记该信号需要处理。

#### 内核中的信号传递函数

- `send_signal()`：用于发送信号。
- `force_sig()`：用于强制发送信号（如异常情况下）。
- `do_send_sig_info()`：详细实现信号的传递。

### 3. 信号捕获过程

当进程从内核态返回用户态或在用户态执行时，内核会检查是否有未决信号需要处理。如果有，内核会捕获并处理这些信号。

#### 内核中的信号捕获和处理函数

- `do_signal()`：检查和处理未决信号。
- `get_signal()`：从未决信号队列中获取一个信号。
- `handle_signal()`：调用信号处理程序处理信号。

#### `do_signal()` 函数的主要步骤

```c
void do_signal(struct pt_regs *regs)
{
    struct ksignal ksig;
    // 检查是否有未决信号
    if (get_signal(&ksig)) {
        // 处理信号
        handle_signal(&ksig, regs);
    }
}
```

### 4. 信号处理

信号处理程序是由用户定义的函数，用于处理特定的信号。内核在捕获到信号后，会调用相应的信号处理程序。

#### `handle_signal()` 函数的主要步骤

```c
void handle_signal(struct ksignal *ksig, struct pt_regs *regs)
{
    struct k_sigaction *ka = &current->sighand->action[ksig->sig];
    // 调用用户定义的信号处理程序
    ka->sa.sa_handler(ksig->sig);
    // 处理完成后恢复进程执行状态
    restore_sigcontext(regs);
}
```

### 5. 数据结构

#### `task_struct`

每个进程的核心数据结构，包含进程的状态、调度信息、信号信息等。
- `sigpending pending`：存储进程的未决信号队列。
- `sigset_t blocked`：存储进程的阻塞信号集。
- `struct signal_struct *signal`：指向信号结构体，包含进程组的信号信息。
- `struct sighand_struct *sighand`：指向信号处理程序的结构体。

#### `signal_struct`

存储进程组的信号信息，包括共享的未决信号。
- `struct sigpending shared_pending`：存储进程组的共享未决信号队列。
- `atomic_t count`：引用计数。

#### `sighand_struct`

存储信号处理程序信息。
- `struct k_sigaction action[_NSIG]`：每个信号对应的处理程序。
- `refcount_t count`：引用计数。
- `spinlock_t siglock`：自旋锁，用于保护信号处理程序的操作。

#### `sigpending`

存储未决信号的信息。
- `sigset_t signal`：存储未决信号的位图。
- `struct list_head list`：未决信号的链表。

#### `k_sigaction`

表示每个信号的处理程序。
- `struct sigaction sa`：实际的信号处理程序，包括处理程序的地址、信号掩码等。

### 6. 示例代码

以下是一个完整的信号捕获和处理示例，演示了如何设置和处理 `SIGINT` 信号：

```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

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
        exit(EXIT_FAILURE);
    }

    printf("Press Ctrl+C to trigger SIGINT\n");
    while (1) {
        pause(); // 等待信号
    }

    return 0;
}
```

在这个示例中，用户按下 Ctrl+C 后，终端驱动程序生成 `SIGINT` 信号，并传递到前台进程。内核捕获到信号后，调用 `handle_sigint` 函数处理信号。

通过以上详细解释，希望能帮助你理解 Linux 内核中捕获信号的过程。如果有更多问题或需要进一步的解释，请随时告诉我！