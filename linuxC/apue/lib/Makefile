# 编译一个so

all: liberror.so

clean:
	rm -f liberror.so

CFLAGS = -shared -fPIC

liberror.so: error.c
	gcc -o liberror.so error.c -g -Wall $(CFLAGS) -I ../include
