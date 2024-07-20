# 一些工具链接

TODO：利用LLM的能力形成更系统的文档

## 2.命令行环境

### 2.3 查找文件

    find <path> -name "file_name" -size <"+1G"> -or -type d

### 2.4 压缩文件

    tar -cz -f <target.tar.gz> <file1> <file2> <file3>

### 2.5 文本替换

    sed 's/origin/to_replace/g' <file_name>

### 3.2 操作系统

`操作系统导论` https://github.com/remzi-arpacidusseau/ostep-code

## 4. 设计模式

[图说设计模式](https://design-patterns.readthedocs.io/zh-cn/latest/)
[22种设计模式(不开代理)](https://refactoringguru.cn/design-patterns/catalog)

## 5. Linux基础

### 5.1 中科大Linux101

[Linux101](https://101.lug.ustc.edu.cn/)

### 5.2 快速教程

[linux工具快速教程](https://linuxtools-rst.readthedocs.io/zh-cn/latest/)

## 6. 文档

### 6.1 markdown

[编写整洁优雅的Markdown](https://roc-mountain.github.io/Markdown/)


https://blog.seisman.info/

[Git 版本控制：构建高效协作和开发流程的最佳实践](https://cloud.tencent.com/developer/article/2412186)


# 构建工具

## 1. gcc

[南洋理工网站](https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html)

## 2. GNU make

[GNU make官方文档 PDF](https://www.gnu.org/software/make/manual/make.pdf)

[跟我一起写Makefile PDF](https://seisman.github.io/how-to-write-makefile/Makefile.pdf)

## 3. Modern cmake

[现代cmake](https://modern-cmake-cn.github.io/Modern-CMake-zh_CN/)

[英文版PDF](https://cliutils.gitlab.io/modern-cmake/modern-cmake.pdf)

[cmake的基本使用](https://zhuanlan.zhihu.com/p/614781589)

[cmake tutorial中文版翻译](https://github.com/chaneyzorn/CMake-tutorial)

# 版本控制工具 git


## 1. 参考资料

### 1.1 网站

[Git 版本控制：构建高效协作和开发流程的最佳实践](https://cloud.tencent.com/developer/article/2412186)

## 2. 命令速查

### basic
```shell
git init
git clone <URL>
git status
git add .
git commit -m "message"
```

### branch

```shell
git branch
git branch -r
git branch -a
git remote -v
git remote add <upstream> <URL>
git pull origin master -r
git push origin master -f
git checkout -b <new_branch> <upstream>/<master>
git commit --amend
git push origin --delete <remote_branch_name>
git branch -D <local_branch_name>
```

### rollback

```shell
git restore <file_name>
git reset hard <sha40_value>
```
