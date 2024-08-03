# 用于linux kernel developing的根Makefile

KDIR := /home/CLionProjects/scratch/linux-6.8.5

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
