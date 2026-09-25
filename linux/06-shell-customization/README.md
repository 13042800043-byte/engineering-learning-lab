# Shell 配置、别名与插件

> 首次记录：2026-09-24

## 配置层次

课程中接触了以下概念：

- dotfiles：以 `.` 开头的配置文件；
- alias：为常用命令和选项设置简写；
- Shell 插件：增加补全、语法高亮、历史建议或提示符等能力；
- `$PATH`：Shell 查找可执行程序的目录列表。

常见配置文件包括：

```text
Bash：~/.bashrc、~/.bash_profile
Zsh： ~/.zshrc
SSH： ~/.ssh/config
tmux：~/.tmux.conf
```

插件本质上仍是加载到环境中的代码，可能影响启动速度、快捷键、补全行为和安全性。学习原则是先理解原生命令，再安装确实需要的插件。

## 当前状态

- 已通过课程了解配置文件、别名和插件的用途。
- 本次没有确认实际安装 Shell 插件或修改 dotfiles。

## 官方资料

- [MIT Missing Semester：Customizing the Shell](https://missing.csail.mit.edu/2026/command-line-environment/#customizing-the-shell)
- [GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
