在内核或应用程序开发中，可以使用编译宏来实现不同的日志级别。这样可以在编译时控制日志输出的详细程度，而不需要修改代码。以下是一个示例，演示如何使用编译宏实现日志级别。

### 示例代码

1. **定义日志级别**：
   首先，定义不同的日志级别。通常使用枚举来表示日志级别，并定义相应的宏。

   ```c
   #ifndef LOG_H
   #define LOG_H

   #include <stdio.h>

   // 定义日志级别
   typedef enum {
       LOG_LEVEL_EMERG,   // 0: 紧急信息
       LOG_LEVEL_ALERT,   // 1: 警报信息
       LOG_LEVEL_CRIT,    // 2: 关键条件
       LOG_LEVEL_ERR,     // 3: 错误条件
       LOG_LEVEL_WARNING, // 4: 警告条件
       LOG_LEVEL_NOTICE,  // 5: 通知信息
       LOG_LEVEL_INFO,    // 6: 信息性消息
       LOG_LEVEL_DEBUG    // 7: 调试信息
   } log_level_t;

   // 设置默认日志级别
   #ifndef LOG_LEVEL
   #define LOG_LEVEL LOG_LEVEL_DEBUG
   #endif

   // 日志宏
   #define LOG(level, fmt, ...) \
       do { \
           if (level <= LOG_LEVEL) { \
               printf("[%s] " fmt "\n", log_level_str(level), ##__VA_ARGS__); \
           } \
       } while (0)

   // 获取日志级别字符串
   static inline const char *log_level_str(log_level_t level) {
       switch (level) {
           case LOG_LEVEL_EMERG: return "EMERG";
           case LOG_LEVEL_ALERT: return "ALERT";
           case LOG_LEVEL_CRIT: return "CRIT";
           case LOG_LEVEL_ERR: return "ERR";
           case LOG_LEVEL_WARNING: return "WARNING";
           case LOG_LEVEL_NOTICE: return "NOTICE";
           case LOG_LEVEL_INFO: return "INFO";
           case LOG_LEVEL_DEBUG: return "DEBUG";
           default: return "UNKNOWN";
       }
   }

   #endif // LOG_H
   ```

2. **使用日志宏**：
   在程序中使用定义好的日志宏记录不同级别的日志消息。

   ```c
   #include "log.h"

   int main() {
       LOG(LOG_LEVEL_EMERG, "This is an emergency message");
       LOG(LOG_LEVEL_ALERT, "This is an alert message");
       LOG(LOG_LEVEL_CRIT, "This is a critical message");
       LOG(LOG_LEVEL_ERR, "This is an error message");
       LOG(LOG_LEVEL_WARNING, "This is a warning message");
       LOG(LOG_LEVEL_NOTICE, "This is a notice message");
       LOG(LOG_LEVEL_INFO, "This is an info message");
       LOG(LOG_LEVEL_DEBUG, "This is a debug message");

       return 0;
   }
   ```

3. **编译时控制日志级别**：
   在编译时，可以通过定义 `LOG_LEVEL` 宏来控制日志级别。例如，要设置日志级别为 `LOG_LEVEL_WARNING`（只显示警告及以上级别的日志），可以这样编译：

   ```bash
   gcc -DLOG_LEVEL=LOG_LEVEL_WARNING -o log_example log_example.c
   ```

### 解释

- **日志级别定义**：
  使用枚举类型定义了多个日志级别，每个级别对应一个整数值，表示其优先级。

- **默认日志级别**：
  使用宏 `LOG_LEVEL` 来定义默认日志级别。如果未在编译时指定，将使用 `LOG_LEVEL_DEBUG` 作为默认级别。

- **日志宏**：
  `LOG` 宏用于记录日志消息。它会检查消息级别是否小于或等于当前日志级别，如果是，则输出日志消息。

- **获取日志级别字符串**：
  `log_level_str` 函数用于将日志级别转换为相应的字符串，以便在日志消息中显示。

### 优点

- **灵活性**：
  可以在编译时轻松控制日志输出的详细程度，而无需修改源代码。

- **性能**：
  由于日志级别检查是在编译时进行的，未达到日志级别的消息不会被编译到最终的可执行文件中，从而减少了运行时的性能开销。

通过这种方式，开发人员可以根据需要调整日志输出的详细程度，方便在开发、测试和生产环境中进行调试和监控。