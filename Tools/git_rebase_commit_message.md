你可以使用 `git rebase` 来合并这三个提交，只保留一个 commit message。具体步骤如下：

1. 查看你的提交历史，找到你想要合并的那三个提交之前的提交哈希。例如，你可以使用 `git log` 来查看提交历史：

   ```sh
   git log
   ```

2. 假设你想要合并的三个提交之前的提交哈希是 `abc123`。那么你可以开始交互式 rebase：

   ```sh
   git rebase -i abc123
   ```

3. 在编辑器中，你会看到类似以下内容：

   ```plaintext
   pick commit1_hash commit message 1
   pick commit2_hash commit message 2
   pick commit3_hash commit message 3
   ```

   将 `pick` 改为 `squash` 或 `s`，除了第一个提交外。例如：

   ```plaintext
   pick commit1_hash commit message 1
   squash commit2_hash commit message 2
   squash commit3_hash commit message 3
   ```

4. 保存并关闭编辑器。接下来，Git 会提示你编辑合并后的 commit message。你可以根据需要修改，然后保存并关闭编辑器。

完成之后，Git 会将这三个提交合并为一个，并保留你设置的 commit message。

如果你遇到任何冲突，解决冲突后继续 rebase：

```sh
git rebase --continue
```

最终，你会得到一个包含所有更改的单一提交，并且只保留你设置的 commit message。