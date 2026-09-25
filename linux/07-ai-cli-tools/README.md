# AI 命令行工具

> 首次记录：2026-09-24

## `llm` 的定位

课程中的 `llm` 是一个可安装的命令行 AI 工具，不是 Linux 内置命令。它可以从参数或 stdin 接收文本，并把模型结果写到 stdout，因此也能加入命令管道。

与 `grep` 的区别：

```text
grep：确定性的字符串或正则搜索，快速、稳定、便于定位原文
LLM：概率性的语义理解，适合归类和总结，但可能理解错误或杜撰
```

在学习检测中已经能够根据场景选择：

- 搜索大量文件中的明确字符串时，优先使用 `grep`；
- 归纳格式不统一的错误信息时，可以使用 LLM 辅助；
- LLM 的分类结果需要人工回看原始数据进行验证。

## 安全边界

- 不把密码、密钥和隐私日志直接发送给在线模型；
- 不直接执行看不懂的生成命令；
- 对包含 `sudo`、删除、磁盘操作或网络下载的命令保持警惕。

## 当前状态

- 已理解 `llm` 在命令行数据流中的定位。
- 本次没有确认实际安装或运行 `llm`，也没有确认安装其插件。

## 官方资料

- [MIT Missing Semester：AI in the Shell](https://missing.csail.mit.edu/2026/command-line-environment/#ai-in-the-shell)
- [simonw/llm](https://github.com/simonw/llm)
- [simonw/llm-cmd](https://github.com/simonw/llm-cmd)
