# Root Makefile

obj-y += drivers/hello/
obj-y += drivers/scull/

all:
	make -C /home/CLionProjects/scratch/linux-6.6.43 M=$(PWD) modules

clean:
	make -C /home/CLionProjects/scratch/linux-6.6.43 M=$(PWD) clean
