# simple makefile

all: ls1 cat1

clean:
	rm -f ls1 cat1

ls1: ls1.c
	gcc -o ls1 ls1.c -Wall -g -I ../include -lerror -L ../lib

cat1: cat1.c
	gcc -o cat1 cat1.c -Wall -g -I ../include -lerror -L ../lib
