# 进程与任务管理命令

> 首次记录：2026-09-25

## 本次接触的流程

```bash
sleep 60 &
sleep_pid=$!
jobs
ps -p "$sleep_pid" -o pid,stat,cmd
kill -TERM "$sleep_pid"
ps -p "$sleep_pid"
```

当前理解：

- `&`：让命令在后台运行；
- `$!`：最近启动的后台任务 PID；
- `jobs`：查看当前 Shell 管理的任务；
- `ps -p`：查询指定 PID 是否仍存在；
- `kill -TERM`：向进程发送正常结束请求。

`kill` 的主要作用是发送信号，并不等同于“查看进程是否结束”。进程收到 `SIGTERM` 后可能退出，也可能处理或忽略它；需要再用 `ps` 等工具检查。

## 当前状态

- 已知道可以用 `ps` 查看进程是否还在运行。
- 本次没有保留实际 `ps` 输出，因此不记录具体状态或结束时间。
- 信号、前后台任务和 `SIGKILL` 的区别仍需继续练习。

## 官方资料

- [Bash Job Control](https://www.gnu.org/software/bash/manual/html_node/Job-Control-Builtins.html)
- [kill Linux Manual Page](https://man7.org/linux/man-pages/man1/kill.1.html)
