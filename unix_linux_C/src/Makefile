ls_wu.out : ls_demo.o error.o
	cc -o ls_wu.out ls_demo.o error.o

ls_demo.o : ls_demo.c ../include/apue.h
	cc -c ls_demo.c
error.o : ../tool/error.c ../include/apue.h
	cc -c ../tool/error.c

clean:
	rm -rf ls_wu.out ls_demo.o error.o