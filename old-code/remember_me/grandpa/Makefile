# 这个makefile文件这样使用：make FILE=main 会编译出out
# 这个makefile文件这样使用：make clean FILE=main 清除main.o out

out : ${FILE}.o
	cc -o out ${FILE}.o

${FILE}.o : ${FILE}.c
	cc -c ${FILE}.c

clean :
	rm -rf out ${FILE}.o

