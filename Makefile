# 用于linux kernel developing的根Makefile

obj-m := hello.o
obj-m := scull.o

KDIR := $(PWD)/linux-6.8.5

all:
	make -C $(KDIR) M=$(PWD)/drivers/hello_module module
	make -C $(KDIR) M=$(PWD)/drivers/scull module

clean:
	make -C $(KDIR) M=$(PWD)/drivers/hello_module clean
	make -C $(KDIR) M=$(PWD)/drivers/scull clean
