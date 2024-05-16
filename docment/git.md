# 版本控制工具 git


## 1. 参考资料

### 1.1 网站

[Git 版本控制：构建高效协作和开发流程的最佳实践](https://cloud.tencent.com/developer/article/2412186)

### 1.2 textbook

[Progit](https://git-scm.com/book/zh/v2)

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
