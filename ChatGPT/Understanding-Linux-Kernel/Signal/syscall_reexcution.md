当内核不能立即满足系统调用发出的请求时，进程可能会进入一种等待状态。等待状态可以是等待 I/O 完成、资源可用等。在这种情况下，如果有信号传递过来，内核将处理信号，并可能重新执行被中断的系统调用。这个过程涉及多个步骤和数据结构。下面详细解释这个过程。

### 1. 进程进入等待状态

当进程执行某个系统调用（如 `read()` 或 `write()`）时，如果内核不能立即满足请求（例如等待磁盘 I/O 完成），进程将进入等待状态。

- **进程状态**：`TASK_INTERRUPTIBLE` 或 `TASK_UNINTERRUPTIBLE`。
- **等待队列**：进程被加入到相应的等待队列中。

### 2. 等待事件发生

进程在等待队列中等待事件发生（如 I/O 完成）。此时进程不会占用 CPU 资源。

### 3. 信号传递

当信号传递到等待中的进程时，内核需要处理该信号。信号可以是由其他进程发送的，也可以是硬件事件或内核内部事件产生的。

### 4. 唤醒进程

如果进程处于 `TASK_INTERRUPTIBLE` 状态，信号的到达会导致进程从等待队列中被唤醒。进程状态被设置为 `TASK_RUNNING`，并被重新调度执行。

### 5. 信号处理

进程被唤醒后，内核会检查是否有未决信号需要处理。如果有，内核会处理这些信号。

#### 5.1 检查和处理信号

内核在进程上下文切换时或者从内核态返回用户态时，会调用 `do_signal()` 检查和处理未决信号。

```c
void do_signal(struct pt_regs *regs)
{
    struct ksignal ksig;
    if (get_signal(&ksig)) {
        handle_signal(&ksig, regs);
    }
}
```

### 6. 重新执行系统调用

在信号处理完成后，内核会检查是否需要重新执行被中断的系统调用。这通常通过重新设置系统调用参数和重新调用系统调用入口来实现。

#### 6.1 系统调用重启

- **系统调用重启标志**：如果系统调用可以被重启，内核会设置 `SA_RESTART` 标志。
- **重启机制**：内核会重新执行被中断的系统调用。

#### 示例：系统调用重启代码

```c
asmlinkage long sys_read(unsigned int fd, char __user *buf, size_t count)
{
    ssize_t ret;
    ret = do_read(fd, buf, count);
    if (ret == -EINTR && (current->flags & PF_RESTART)) {
        ret = do_read(fd, buf, count);
    }
    return ret;
}
```

在这个示例中，`sys_read` 系统调用在第一次执行 `do_read` 时被信号中断（返回 `-EINTR`）。如果当前进程的标志 `PF_RESTART` 被设置，系统调用将被重启并重新执行 `do_read`。

### 详细过程示例

以下是一个详细的过程示例，演示了进程在等待 I/O 时被信号中断并重新执行系统调用：

1. **进程调用 `read()` 系统调用**：
    - 用户进程调用 `read(fd, buf, count)`。
    - 内核无法立即满足请求，进程进入 `TASK_INTERRUPTIBLE` 状态并等待 I/O 完成。

2. **进程等待 I/O 完成**：
    - 进程在等待队列中等待 I/O 完成。

3. **信号到达**：
    - 另一个进程发送信号（如 `SIGINT`）给等待中的进程。

4. **唤醒进程**：
    - 信号到达后，内核唤醒等待中的进程，将其状态设置为 `TASK_RUNNING`。

5. **处理信号**：
    - 进程被唤醒后，内核调用 `do_signal()` 检查和处理未决信号。
    - 内核调用信号处理程序处理信号。

6. **重新执行系统调用**：
    - 信号处理完成后，内核检查 `SA_RESTART` 标志。
    - 如果标志被设置，内核重新执行 `read()` 系统调用。

### 代码示例：等待和信号处理

以下是一个示例程序，演示了进程在等待 `read()` 系统调用时被 `SIGINT` 信号中断并重新执行系统调用的过程：

```c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

void handler(int sig) {
    printf("Caught signal %d\n", sig);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    int fd = open("testfile", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char buf[10];
    ssize_t ret = read(fd, buf, sizeof(buf));
    if (ret == -1) {
        if (errno == EINTR) {
            printf("read was interrupted by signal\n");
        } else {
            perror("read");
        }
    } else {
        printf("read %zd bytes\n", ret);
    }

    close(fd);
    return 0;
}
```

在这个程序中，`sigaction` 设置了一个处理 `SIGINT` 信号的处理程序，并设置 `SA_RESTART` 标志。`read()` 系统调用被 `SIGINT` 信号中断时，会自动重启。

通过以上详细解释，希望能帮助你理解 Linux 内核中进程在等待系统调用时被信号中断并重新执行系统调用的过程。如果有更多问题或需要进一步的解释，请随时告诉我！