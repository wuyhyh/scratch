//
// Created on 2024/3/30.
//

// This is our own header, include it before all standard system headers

#ifndef APUE_H
#define APUE_H

#define _POSIX_C_SOURCE 200809L // limitation

#include <sys/types.h> // some system still need this
#include <sys/stat.h>
#include <sys/termios.h> // for winsize 我也不懂这是啥意思

#if defined(MACOS) || defined(TIOCGWINSZ)
#include <sys/ioctl.h>
#endif

#include <stdio.h> /* for convenience */
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define MAXLINE 4096

// default file access permissions for new files
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

// default permissions for new directories
#define DIR_MODE (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)

typedef void Sigfunc(int); // for signal handlers

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

// Prototypes for our own functions
char *path_alloc(size_t *);
long open_max(void);

int set_cloexec(int);
void clr_fl(int, int);
void set_fl(int, int);

void pr_exit(int);

void pr_mask(const char *);
Sigfunc *signal_intr(int, Sigfunc *);

void daemonize(const char *);

void sleep_us(unsigned int);
ssize_t readn(int, void *, size_t);
ssize_t writen(int, const void *, size_t);

int fd_pipe(int *);

// 锁
int lock_reg(int, int, int, off_t, int, off_t);

#define read_lock(fd, offset, whence, len) \
	lock_reg((fd), F_SETLK, F_RDLCK, (offset), (whence), (len))

#define readw_lock(fd, offset, whence, len) \
	lock_reg((fd), F_SETLKW, F_RDLCK, (offset), (whence), (len))

#define write_lock(fd, offset, whence, len) \
	lock_reg((fd), F_SETLKW, F_WRLCK, (offset), (whence), (len))

#define writew_lock(fd, offset, whence, len) \
	lock_reg((fd), F_SETLKW, F_WRLCK, (offset), (whence), (len))

#define un_lock(fd, offset, whence, len) \
	lock_reg((fd), F_SETLK, F_UNLCK, (offset), (whence), (len))

pid_t lock_test(int, int, off_t, int, off_t);

#define is_read_lockable(fd, offset, whence, len) \
	(lock_test((fd), F_RDLCK, (offset), (whence), (len)) == 0)

#define is_write_lockable(fd, offset, whence, len) \
	(lock_test((fd), F_WRLCK, (offset), (whence), (len)) == 0)

// 标准错误函数
void err_msg(const char *, ...);
void err_dump(const char *, ...) __attribute__((noreturn));
void err_quit(const char *, ...) __attribute__((noreturn));
void err_cont(int, const char *, ...);
void err_exit(int, const char *, ...) __attribute__((noreturn));
void err_ret(const char *, ...);
void err_sys(const char *, ...) __attribute__((noreturn));

// 日志打印函数
void log_msg(const char *, ...);
void log_open(const char *, int, int);
void log_quit(const char *, ...);
__attribute__((noreturn));
void log_ret(const char *, ...);
void log_sys(const char *, ...) __attribute__((noreturn));
void log_exit(const char *, ...) __attribute__((noreturn));

// 进程相关的函数宏
void TELL_WAIT(void);
void TELL_PARENT(pid_t);
void TELL_CHILD(pid_t);
void WAIT_PARENT(void);
void WAIT_CHILD(void);

#endif // APUE_H
