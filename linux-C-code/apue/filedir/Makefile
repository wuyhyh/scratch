all: filetype

clean:
	rm -f filetype

filetype: filetype.c
	gcc -o filetype filetype.c -O -g -Wall -I ../include -lerror -L ../lib
