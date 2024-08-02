# 用于linux kernel developing的根Makefile

obj-m := my_module.o

KDIR := $(PWD)/linux-6.8.5

all:
	make -C $(KDIR) M=$(PWD)/drivers/hello_module hello

clean:
	make -C $(KDIR) M=$(PWD)/drivers/hello_module clean

