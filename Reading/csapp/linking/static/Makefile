all: prog2

prog2: main2.o libvector.a
	gcc -o prog2 main2.o --static libvector.a -L ./

main2.o: main2.c
	gcc -o main2.o main2.c

libvector.a: addvec.o multvec.o
	ar addvec.o multvec.o

addvec.o: addvec.c
	gcc -o addvec.o addvec.c

multvec.o: multvec.c
	gcc -o multvec.o multvec.c
