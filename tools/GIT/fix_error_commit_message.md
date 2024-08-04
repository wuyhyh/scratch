要修改历史 Git 提交中的错别字，可以使用 `git rebase` 和 `git commit --amend` 命令。以下是具体步骤：

### 修改最近一次提交的错别字
1. 打开终端，进入你的 Git 仓库目录。
2. 使用 `git commit --amend` 命令编辑最近一次提交的消息：

   ```bash
   git commit --amend
   ```

3. 编辑提交消息，修正错别字，然后保存并退出编辑器。

### 修改更早的提交记录
1. 找到你想要修改的提交记录的哈希值。你可以使用 `git log` 命令查看提交历史：

   ```bash
   git log
   ```

2. 使用 `git rebase -i <commit>` 命令进入交互式 rebase 模式，其中 `<commit>` 是你想要修改的提交之前的那个提交的哈希值。例如，如果你想修改倒数第二次提交，使用：

   ```bash
   git rebase -i HEAD~2
   ```

3. 在打开的编辑器中，你会看到类似以下的内容：

   ```
   pick <commit_hash> Commit message 1
   pick <commit_hash> Commit message 2
   ```

   把你想要修改的提交记录的 `pick` 改为 `edit`，然后保存并退出编辑器。

4. 现在，Git 会暂停在你想要修改的提交。使用 `git commit --amend` 命令编辑提交消息：

   ```bash
   git commit --amend
   ```

5. 编辑提交消息，修正错别字，然后保存并退出编辑器。

6. 使用 `git rebase --continue` 命令完成 rebase：

   ```bash
   git rebase --continue
   ```

### 注意事项
- 如果你已经将这些提交推送到远程仓库，你需要强制推送更新：

  ```bash
  git push --force
  ```

  请谨慎使用 `--force`，因为这会覆盖远程仓库中的历史记录，可能会影响其他开发者。

- 确保所有团队成员都了解你在强制推送之前的更改，以避免冲突和数据丢失。
