# 这个makefile文件这样使用：make FILE=main 会编译出out
# 这个makefile文件这样使用：make clean FILE=main 清除main.o out

out : ${FILE}.o
	cc -o out ${FILE}.o

${FILE}.o : ${FILE}.c
	cc -c ${FILE}.c

clean :
	rm -rf out ${FILE}.o

# 与此无关的代码。消除rdma-core编译中的依赖错误
# sed -i 's/-DIN_PLACE=1/-DIN_PLACE=0 -DENABLE_RESOLVE_NEIGH=0/' build.sh