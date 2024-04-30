# 这个makefile文件这样使用：make FILE=main 会编译出out
# 这个makefile文件这样使用：make clean FILE=main 清除main.o out

all: yeye

clean :
	rm -f yeye

yeye: grandpa.c
	gcc -o yeye grandpa.c -Wall -g -O2
