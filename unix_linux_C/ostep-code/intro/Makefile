# 一种简单高效的makefile写法

SRCS = cpu.c

TARG = cpu

CC = gcc
OPTS = -O -Wall
LIBS = -lm

# 这里把.c文件translate成.o文件
OBJS = $(SRCS:.c=.o)

# 产生target ELF文件
all : $(TARG)

# 链接行
$(TARG) : $(OBJS)
	$(CC) -o $(TARG) $(OBJS) $(LIBS)

# 编译行
%.o : %.c
	$(CC) $(OPTS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(TARG)
