//
// Created on 2024/3/30.
//

// This is our own header, include it before all standard system headers

#ifndef APUE_H
#define APUE_H

#define _POSIX_C_SOURCE 200809L

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

void err_quit(const char *, ...) __attribute__((noreturn));
void err_sys(const char *, ...) __attribute__((noreturn));

#endif // APUE_H
