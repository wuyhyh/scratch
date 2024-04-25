ls_wu.out : ls_demo.o error.o
	cc -o ls_wu.out ls_demo.o error.o

ls_demo.o : ls_demo.c ../apue-code/include
	cc -c ls_demo.c
error.o : ../../linux-C-code/apue-code/error.c ../apue-code/include
	cc -c ../tool/error.c

clean:
	rm -rf ls_wu.out ls_demo.o error.o