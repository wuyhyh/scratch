控制台日志级别（console log level）定义了哪些优先级的日志消息会被输出到控制台。控制台日志级别的设定可以控制在控制台上显示的消息的详细程度。`printk`函数用于内核中记录日志消息，每条消息都有一个优先级。当消息的优先级低于或等于控制台日志级别时，这条消息会被输出到控制台。

### 控制台日志级别的值和含义

控制台日志级别是一个整数值，对应于`printk`消息的优先级。优先级的取值范围及其含义如下：

| 数值 | 宏定义          | 描述                               |
|------|-----------------|------------------------------------|
| 0    | KERN_EMERG      | 紧急信息，表示系统不可用。         |
| 1    | KERN_ALERT      | 警报信息，需要立即采取行动。       |
| 2    | KERN_CRIT       | 关键条件，表示严重错误。           |
| 3    | KERN_ERR        | 错误条件，表示一般错误。           |
| 4    | KERN_WARNING    | 警告条件，表示可能出现问题的情况。 |
| 5    | KERN_NOTICE     | 通知信息，表示正常但重要的情况。   |
| 6    | KERN_INFO       | 信息性消息，表示普通信息。         |
| 7    | KERN_DEBUG      | 调试信息，表示调试相关信息。       |

### 修改控制台日志级别

可以通过多种方式修改控制台日志级别：

1. **命令行参数**：
   在内核启动时，可以通过命令行参数`loglevel`来设置控制台日志级别。例如，要设置控制台日志级别为`4`（警告），可以在启动参数中添加：

   ```
   loglevel=4
   ```

2. **`/proc`文件系统**：
   在系统运行时，可以通过修改`/proc/sys/kernel/printk`文件来设置控制台日志级别。该文件包含四个值，分别是：

   ```
   current default minimum boot-time-default
   ```

   其中，`current`表示当前的控制台日志级别。可以使用`echo`命令修改：

   ```bash
   # 显示当前控制台日志级别
   cat /proc/sys/kernel/printk

   # 设置控制台日志级别为4（警告）
   echo 4 > /proc/sys/kernel/printk
   ```

3. **`printk`函数**：
   还可以通过`printk`函数在内核代码中动态修改控制台日志级别。例如：

   ```c
   // 设置控制台日志级别为4（警告）
   printk(KERN_INFO "Setting console log level to WARNING\n");
   console_loglevel = 4;
   ```

### 控制台日志级别与`printk`的关系

`printk`函数用于记录日志消息，每条消息都有一个优先级。当消息的优先级低于或等于当前控制台日志级别时，这条消息会被输出到控制台。例如：

```c
printk(KERN_INFO "This is an info message\n"); // KERN_INFO (6)
printk(KERN_WARNING "This is a warning message\n"); // KERN_WARNING (4)
```

如果当前的控制台日志级别是`4`（KERN_WARNING），那么只有第二条消息（警告）会被输出到控制台，第一条消息（信息）不会被输出。

通过合理设置控制台日志级别，可以控制在控制台上显示的日志消息的详细程度，有助于在开发和调试过程中有效地获取所需的信息。