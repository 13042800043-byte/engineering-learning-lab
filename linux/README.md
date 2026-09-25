# Linux Learning

本目录用于记录我的 Linux 学习过程、命令实验、Linux C/C++ 开发实践，以及后续 Embedded Linux 相关内容。

当前 Linux 的学习目标并不是单纯掌握大量命令，而是逐渐建立：

> **Linux 开发环境 + 系统编程 + 嵌入式 Linux**

的完整认知。

---

# 1. Learning Goal

当前阶段希望逐渐具备以下能力：

- 熟练使用 Linux 命令行环境
- 能够独立管理文件、权限、进程和软件
- 能够在 Linux 下编译、运行和调试 C/C++ 程序
- 掌握 GCC / G++ / Make / CMake / GDB
- 理解 Linux Process / Thread
- 理解基本 IPC 机制
- 掌握 Socket 网络编程基础
- 能够在 Linux 下运行 OpenCV / C++ 项目
- 能够通过 SSH 使用远程 Linux 设备
- 为后续 ARM Linux / Embedded Linux 开发建立基础

长期希望形成：

```text
C / C++
   ↓
Linux Development
   ↓
System Programming
   ↓
Embedded Linux
   ↓
OpenCV / AI Deployment
   ↓
Embedded Vision
```

---

# 2. Command Categories

Linux 命令学习成果按用途分类存放，而不是把所有命令写入同一篇笔记：

```text
linux/
├── 01-shell-basics/          # Shell、命令结构、参数、数据流
├── 02-text-processing/       # grep、sort、uniq、cut 等文本处理
├── 03-permissions/           # chmod、文件权限、sudo
├── 04-process-management/    # ps、jobs、kill、信号与任务
├── 05-network-remote/        # SSH、远程命令与网络工具
├── 06-shell-customization/   # dotfiles、alias、插件与 PATH
└── 07-ai-cli-tools/          # llm 等 AI 命令行工具
```

## Current Notes

- [Shell 与命令基础](01-shell-basics/README.md)
- [文本搜索与处理命令](02-text-processing/README.md)
- [用户、权限与 sudo](03-permissions/README.md)
- [进程与任务管理命令](04-process-management/README.md)
- [网络与远程命令](05-network-remote/README.md)
- [Shell 配置、别名与插件](06-shell-customization/README.md)
- [AI 命令行工具](07-ai-cli-tools/README.md)

## Recording Rule

- 分类目录记录对应命令的用途、参数、实验和理解；
- Weekly Log 记录学习日期与本周进度；
- 未亲自执行的命令只记录为课程学习或待实践，不写成已完成实验；
- 同一个命令如果涉及多个主题，以主要用途归类，并通过链接关联其他板块。
