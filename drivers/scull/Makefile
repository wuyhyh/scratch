# Makefile

# 内核模块的编译
obj-m += scull.o

all: scull_test
	make -C /home/CLionProjects/scratch/linux-6.6.43 M=$(PWD) modules

scull_test: CMakeLists.txt
	@mkdir -p build
	@cd build && cmake ..
	@cd build && make

clean:
	make -C /home/CLionProjects/scratch/linux-6.6.43 M=$(PWD) clean
	@rm -rf build
