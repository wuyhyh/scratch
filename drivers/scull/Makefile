obj-m += scull.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) scull

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean