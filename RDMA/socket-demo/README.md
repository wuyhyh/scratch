好的，我将为您编写两个 C 语言程序：一个作为服务器（server），一个作为客户端（client），用于在两台虚拟机之间通过套接字（socket）传输文本文件。代码将包含详细的注释，以帮助您理解每个部分的功能。

---

## **总体思路**

- **服务器程序**：在指定端口上监听连接请求，接受来自客户端的文件，并将其保存到本地。
- **客户端程序**：连接到服务器，读取指定的文本文件内容，并通过套接字发送给服务器。

---

## **服务器代码（server.c）**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>         // close() 函数
#include <arpa/inet.h>      // 套接字函数及数据结构
#include <sys/socket.h>     // 套接字函数及数据结构
#include <netinet/in.h>     // 套接字地址结构

#define PORT 8080           // 服务器监听的端口号
#define BUFFER_SIZE 1024    // 缓冲区大小

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    FILE *file;

    // 1. 创建套接字
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("套接字创建失败");
        exit(EXIT_FAILURE);
    }

    // 2. 绑定地址和端口
    address.sin_family = AF_INET;            // 使用 IPv4 地址族
    address.sin_addr.s_addr = INADDR_ANY;    // 接受任意 IP 地址的连接
    address.sin_port = htons(PORT);          // 端口号，使用 htons 转换为网络字节序

    // 绑定套接字到指定地址和端口
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("绑定失败");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 3. 开始监听
    if (listen(server_fd, 3) < 0) {
        perror("监听失败");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("服务器正在监听端口 %d...\n", PORT);

    // 4. 接受客户端连接
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
        perror("接受连接失败");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("接受到来自客户端的连接。\n");

    // 5. 接收文件内容并保存
    file = fopen("received_file.txt", "w");
    if (file == NULL) {
        perror("无法创建文件");
        close(new_socket);
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("正在接收文件...\n");

    while ((bytes_read = read(new_socket, buffer, BUFFER_SIZE)) > 0) {
        fwrite(buffer, sizeof(char), bytes_read, file);
    }

    printf("文件接收完成，保存为 'received_file.txt'。\n");

    // 6. 关闭文件和套接字
    fclose(file);
    close(new_socket);
    close(server_fd);

    return 0;
}
```

---

## **客户端代码（client.c）**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>         // close() 函数
#include <arpa/inet.h>      // 套接字函数及数据结构
#include <sys/socket.h>     // 套接字函数及数据结构
#include <netinet/in.h>     // 套接字地址结构

#define PORT 8080           // 服务器监听的端口号
#define BUFFER_SIZE 1024    // 缓冲区大小

int main(int argc, char const *argv[]) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE];
    FILE *file;
    ssize_t bytes_read;

    // 检查命令行参数，确保提供了文件名和服务器 IP
    if (argc != 3) {
        printf("用法：%s <服务器IP地址> <文件路径>\n", argv[0]);
        return -1;
    }

    const char *server_ip = argv[1];   // 服务器 IP 地址
    const char *file_path = argv[2];   // 要发送的文件路径

    // 1. 创建套接字
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("套接字创建失败");
        return -1;
    }

    // 2. 设置服务器地址和端口
    serv_addr.sin_family = AF_INET;                // 使用 IPv4 地址族
    serv_addr.sin_port = htons(PORT);              // 端口号，使用 htons 转换为网络字节序

    // 将 IP 地址从文本转换为二进制形式
    if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0) {
        printf("无效的地址/地址不支持：%s\n", server_ip);
        close(sock);
        return -1;
    }

    // 3. 连接到服务器
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("连接失败");
        close(sock);
        return -1;
    }
    printf("已连接到服务器 %s:%d。\n", server_ip, PORT);

    // 4. 打开要发送的文件
    file = fopen(file_path, "r");
    if (file == NULL) {
        perror("无法打开文件");
        close(sock);
        return -1;
    }

    printf("正在发送文件 '%s'...\n", file_path);

    // 5. 读取文件内容并发送
    while ((bytes_read = fread(buffer, sizeof(char), BUFFER_SIZE, file)) > 0) {
        if (send(sock, buffer, bytes_read, 0) < 0) {
            perror("发送失败");
            fclose(file);
            close(sock);
            return -1;
        }
    }

    printf("文件发送完成。\n");

    // 6. 关闭文件和套接字
    fclose(file);
    close(sock);

    return 0;
}
```

---

## **编译和运行**

### **在服务器（vm1）上编译和运行服务器程序**

1. **保存 `server.c`**

   将服务器代码复制到 `server.c` 文件中：

   ```bash
   nano server.c
   ```

   将代码粘贴进去，保存并退出。

2. **编译服务器程序**

   ```bash
   gcc server.c -o server
   ```

3. **运行服务器程序**

   ```bash
   ./server
   ```

   程序将开始在端口 `8080` 上监听，并等待客户端连接。

### **在客户端（vm2）上编译和运行客户端程序**

1. **保存 `client.c`**

   将客户端代码复制到 `client.c` 文件中：

   ```bash
   nano client.c
   ```

   将代码粘贴进去，保存并退出。

2. **编译客户端程序**

   ```bash
   gcc client.c -o client
   ```

3. **运行客户端程序**

   假设您要发送的文件路径为 `/home/user/textfile.txt`，并且服务器的 IP 地址是 `192.168.122.185`。

   ```bash
   ./client 192.168.122.185 /home/user/textfile.txt
   ```

   程序将连接到服务器并发送指定的文件。

---

## **详细解释**

### **服务器程序解释（server.c）**

1. **包含必要的头文件**

   ```c
   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   #include <unistd.h>
   #include <arpa/inet.h>
   #include <sys/socket.h>
   #include <netinet/in.h>
   ```

   这些头文件提供了套接字编程所需的函数和数据结构。

2. **定义宏**

   ```c
   #define PORT 8080
   #define BUFFER_SIZE 1024
   ```

   定义服务器监听的端口号和缓冲区大小。

3. **主函数**

   ```c
   int main() {
       // 变量声明
   }
   ```

4. **创建套接字**

   ```c
   server_fd = socket(AF_INET, SOCK_STREAM, 0);
   ```

    - `AF_INET`：使用 IPv4 协议。
    - `SOCK_STREAM`：使用面向连接的 TCP 套接字。
    - 返回的 `server_fd` 是服务器套接字的文件描述符。

5. **绑定地址和端口**

   ```c
   address.sin_family = AF_INET;
   address.sin_addr.s_addr = INADDR_ANY;
   address.sin_port = htons(PORT);
   ```

    - 将服务器的地址和端口绑定到套接字上，使其可以接受客户端连接。

6. **监听连接**

   ```c
   listen(server_fd, 3);
   ```

   开始监听连接请求，`3` 是最大等待连接数。

7. **接受客户端连接**

   ```c
   new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
   ```

   接受一个连接请求，返回新的套接字描述符 `new_socket`。

8. **接收文件内容**

   ```c
   file = fopen("received_file.txt", "w");
   ```

   打开一个文件准备写入接收到的数据。

   ```c
   while ((bytes_read = read(new_socket, buffer, BUFFER_SIZE)) > 0) {
       fwrite(buffer, sizeof(char), bytes_read, file);
   }
   ```

   循环读取客户端发送的数据并写入文件。

9. **关闭文件和套接字**

   ```c
   fclose(file);
   close(new_socket);
   close(server_fd);
   ```

   释放资源。

### **客户端程序解释（client.c）**

1. **包含必要的头文件**

   与服务器程序相同。

2. **定义宏**

   ```c
   #define PORT 8080
   #define BUFFER_SIZE 1024
   ```

3. **主函数**

   ```c
   int main(int argc, char const *argv[]) {
       // 变量声明
   }
   ```

4. **检查命令行参数**

   ```c
   if (argc != 3) {
       printf("用法：%s <服务器IP地址> <文件路径>\n", argv[0]);
       return -1;
   }
   ```

   确保用户提供了服务器 IP 和要发送的文件路径。

5. **创建套接字**

   ```c
   sock = socket(AF_INET, SOCK_STREAM, 0);
   ```

6. **设置服务器地址和端口**

   ```c
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_port = htons(PORT);
   inet_pton(AF_INET, server_ip, &serv_addr.sin_addr);
   ```

7. **连接到服务器**

   ```c
   connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
   ```

8. **打开并发送文件**

   ```c
   file = fopen(file_path, "r");
   while ((bytes_read = fread(buffer, sizeof(char), BUFFER_SIZE, file)) > 0) {
       send(sock, buffer, bytes_read, 0);
   }
   ```

   读取文件内容并通过套接字发送给服务器。

9. **关闭文件和套接字**

   ```c
   fclose(file);
   close(sock);
   ```

---

## **注意事项**

- **端口号**：确保服务器和客户端使用相同的端口号（本例中为 `8080`）。
- **防火墙配置**：在服务器（vm1）上，确保防火墙允许端口 `8080` 的连接。

  ```bash
  sudo firewall-cmd --add-port=8080/tcp --permanent
  sudo firewall-cmd --reload
  ```

- **SELinux（如果启用）**：SELinux 可能会阻止套接字通信，可以暂时将其设置为宽松模式，或者配置策略。

  ```bash
  sudo setenforce 0  # 暂时设置为宽松模式
  ```

- **文件权限**：确保您有权限读取要发送的文件，以及在服务器上有权限写入接收的文件。

---

## **测试**

1. **在服务器（vm1）上运行服务器程序**

   ```bash
   ./server
   ```

   服务器将开始监听并等待客户端连接。

2. **在客户端（vm2）上运行客户端程序**

   ```bash
   ./client 192.168.122.185 /home/user/textfile.txt
   ```

   替换 `/home/user/textfile.txt` 为您要发送的文件路径。

3. **观察服务器输出**

   服务器应该显示接收到连接，并提示文件接收完成。

4. **验证文件传输**

   在服务器（vm1）上，查看当前目录下是否有名为 `received_file.txt` 的文件，内容应与发送的文件一致。

   ```bash
   ls
   cat received_file.txt
   ```

---

## **总结**

通过以上步骤，您可以在两台虚拟机之间使用 C 语言编写的套接字程序实现文件传输。代码中包含了详细的注释，解释了每个步骤的作用。如果您有任何疑问或需要进一步的帮助，请随时告诉我！

