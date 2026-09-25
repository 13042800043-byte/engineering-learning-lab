# Shell 与命令基础

> 首次记录：2026-09-24
>
> 来源：MIT Missing Semester 2026 — Command-line Environment

## 命令结构

常见命令行可以理解为：

```text
程序 [选项] [位置参数]
```

例如：

```bash
grep -rni -- "permission denied" /var/log
```

- `grep`：需要运行的程序；
- `-rni`：传递给 `grep` 的选项；
- `--`：停止选项解析；
- `"permission denied"`：搜索模式；
- `/var/log`：搜索位置。

参数的含义属于具体程序，不能根据另一个命令的同名参数直接推断。遇到陌生参数时，应使用：

```bash
command --help
man command
type command
command -v command
```

## Shell 与程序的分工

当前确认的理解：

```text
Shell：解析引号、变量、通配符和重定向，启动程序并连接数据流
程序：接收参数，完成搜索、排序、复制等具体工作
```

在学习检测中曾把 `grep` 的搜索速度归因于 Shell，复盘后明确：真正读取并搜索文件的是 `grep`，Shell 只负责解析并启动它。

## 数据流

命令行程序通常使用：

- `stdin`：标准输入；
- `stdout`：标准输出；
- `stderr`：标准错误；
- `|`：把前一程序的 stdout 连接到后一程序的 stdin；
- `>`：覆盖写入；
- `>>`：追加写入；
- `2>`：重定向 stderr。

## 当前状态

- 已初步理解程序、选项和位置参数的结构。
- 已明确 Shell 与具体工具的职责不同。
- stdout、stderr 和多重重定向仍需实际练习。

## 官方资料

- [GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
- [MIT Missing Semester：Command-line Environment](https://missing.csail.mit.edu/2026/command-line-environment/)
