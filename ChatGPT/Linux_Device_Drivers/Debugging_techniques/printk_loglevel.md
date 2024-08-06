在使用`printk`进行调试时，可以使用不同的日志级别来标记消息的严重性和重要性。Linux内核定义了以下几种常见的日志级别，每个级别都有其特定的作用：

| 日志级别    | 描述                                            | 宏定义                 |
|-------------|-------------------------------------------------|------------------------|
| **KERN_EMERG** | 紧急信息，表示系统处于不可用状态，通常用于严重错误。    | `"<0>"`                |
| **KERN_ALERT** | 警报信息，表示需要立即采取行动，通常用于需要立即处理的情况。| `"<1>"`                |
| **KERN_CRIT**  | 关键条件，表示严重的错误条件。                    | `"<2>"`                |
| **KERN_ERR**   | 错误条件，表示一般错误条件。                      | `"<3>"`                |
| **KERN_WARNING** | 警告条件，表示可能会出现问题的情况。               | `"<4>"`                |
| **KERN_NOTICE**  | 通知信息，表示正常但重要的情况。                  | `"<5>"`                |
| **KERN_INFO**   | 信息性消息，表示普通信息。                         | `"<6>"`                |
| **KERN_DEBUG**  | 调试信息，表示调试相关信息。                       | `"<7>"`                |

每个日志级别在`printk`消息中通过一个字符串前缀指定，例如：

```c
printk(KERN_EMERG "This is an emergency message\n");
printk(KERN_ALERT "This is an alert message\n");
printk(KERN_CRIT "This is a critical message\n");
printk(KERN_ERR "This is an error message\n");
printk(KERN_WARNING "This is a warning message\n");
printk(KERN_NOTICE "This is a notice message\n");
printk(KERN_INFO "This is an info message\n");
printk(KERN_DEBUG "This is a debug message\n");
```

以下是每个日志级别的详细作用：

- **KERN_EMERG** (`<0>`): 用于表示系统不可用的紧急情况，例如严重的内核崩溃或硬件故障。
- **KERN_ALERT** (`<1>`): 表示需要立即处理的情况，例如关键的安全问题。
- **KERN_CRIT** (`<2>`): 用于表示关键条件，需要尽快处理的严重错误。
- **KERN_ERR** (`<3>`): 用于报告一般错误条件，例如设备驱动程序中的错误。
- **KERN_WARNING** (`<4>`): 表示可能导致问题的警告条件，需要注意但不一定要立即处理。
- **KERN_NOTICE** (`<5>`): 用于通知正常但重要的情况，例如系统启动完成。
- **KERN_INFO** (`<6>`): 用于报告普通信息，例如驱动程序初始化信息。
- **KERN_DEBUG** (`<7>`): 用于调试信息，帮助开发者追踪和诊断问题。

使用适当的日志级别有助于在系统日志中更有效地分类和过滤消息，从而更快地识别和解决问题。