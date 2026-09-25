# 网络与远程命令

> 首次记录：2026-09-24

## SSH 的本地与远程边界

```bash
ssh server 'grep error app.log' | wc -l
```

学习检测中已经正确判断：

- 引号中的 `grep` 在远程服务器运行；
- 输出通过 SSH 返回本机；
- 引号外的 `wc -l` 在本机运行。

如果写成：

```bash
ssh server 'grep error app.log | wc -l'
```

那么 `grep` 和 `wc` 都在远程运行。

## 当前状态

- 已理解 SSH 可以提供远程 Shell，也可以直接执行远程命令。
- 已初步理解引号和管道位置会影响命令在哪台机器运行。
- 本次没有确认已经实际连接远程服务器，也没有确认已经配置 SSH 密钥。

## 官方资料

- [OpenSSH Manual Pages](https://www.openssh.org/manual.html)
- [MIT Missing Semester：Remote Machines](https://missing.csail.mit.edu/2026/command-line-environment/#remote-machines)
