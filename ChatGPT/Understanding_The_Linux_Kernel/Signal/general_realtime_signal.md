在 Linux 内核中，信号处理机制区分为常规信号和实时信号。这两类信号在发送、排队和处理方面有不同的机制和特性。

### 常规信号和实时信号的区别
1. **常规信号**：
    - 数量有限，通常是从 1 到 31。
    - 不排队，如果同一类型的信号在未处理前多次发送，只会记录一次。
    - 优先级较低，系统中预定义的信号。

2. **实时信号**：
    - 数量较多，通常从 32 到 64（POSIX 标准规定）。
    - 可以排队，保证每个发送的信号都会被处理。
    - 优先级高，可以由用户定义，带有附加数据。

### 常规信号的处理
1. **发送**：
    - 使用系统调用 `kill()`、`raise()` 或其他 IPC 机制。
    - 由内核、用户进程或硬件事件产生。

2. **接收和处理**：
    - 内核在 `task_struct` 中维护一个 `signal_struct`，存储进程的信号信息。
    - 内核通过检查 `pending` 信号位图决定哪些信号需要处理。
    - 当一个信号到达时，内核设置对应的位，并检查该进程是否阻塞了此信号。
    - 如果未阻塞，内核将调用对应的信号处理程序（用户定义的或默认处理程序）。
    - 常规信号不会排队，如果一个信号在未处理前多次发送，只记录一次。

3. **阻塞和未决**：
    - 使用 `sigprocmask()` 可以阻塞某些信号。
    - 阻塞的信号进入未决状态，直到解除阻塞后才会处理。

### 实时信号的处理
1. **发送**：
    - 使用系统调用 `sigqueue()` 发送，可以携带附加数据。
    - 也可以使用 `kill()` 发送，但不能携带附加数据。

2. **接收和处理**：
    - 内核在 `task_struct` 中维护一个 `sigqueue` 队列，用于存储实时信号及其附加数据。
    - 实时信号按顺序排队，不会丢失，保证每个信号都会被处理。
    - 当实时信号到达时，内核将其放入队列，并在合适时调用信号处理程序。

3. **阻塞和未决**：
    - 同样可以使用 `sigprocmask()` 阻塞实时信号。
    - 阻塞的实时信号进入未决状态，并排队等待处理。

### 内核处理信号的主要步骤
1. **发送信号**：
    - 调用 `send_signal()` 函数。
    - 检查信号类型（常规或实时）。
    - 更新目标进程的信号位图（常规信号）或信号队列（实时信号）。

2. **接收信号**：
    - 当进程运行在用户态并返回到内核态时，内核检查是否有未决信号。
    - 使用 `do_signal()` 函数处理未决信号。

3. **处理信号**：
    - 内核根据信号类型和处理策略（忽略、捕获、默认）采取相应的行动。
    - 对于捕获的信号，内核调用用户定义的信号处理程序。

4. **恢复执行**：
    - 信号处理完毕后，内核恢复进程的执行状态。

### 示例代码
以下是一个使用实时信号的示例程序：

```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handle_sigusr1(int sig, siginfo_t *si, void *context) {
    printf("Received SIGUSR1 with value: %d\n", si->si_value.sival_int);
}

int main() {
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handle_sigusr1;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    union sigval value;
    value.sival_int = 42;
    if (sigqueue(getpid(), SIGUSR1, value) == -1) {
        perror("sigqueue");
        exit(EXIT_FAILURE);
    }

    sleep(1); // Wait for signal
    return 0;
}
```

这个程序设置了一个 SIGUSR1 的信号处理程序，并使用 `sigqueue()` 发送一个携带附加数据的实时信号。

希望这些信息对你理解 Linux 内核中的常规信号和实时信号处理机制有所帮助。如果有更多问题或需要更详细的解释，请随时告诉我！