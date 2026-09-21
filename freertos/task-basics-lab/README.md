# FreeRTOS Task Basics Lab

这是一个在 Windows 上运行的 FreeRTOS 入门实验，用于观察：

- 如何使用 `xTaskCreate()` 创建 Task
- 调度器如何根据优先级选择 Ready Task
- Task 调用 `vTaskDelay()` 后如何从 Running 进入 Blocked
- 高、低优先级 Task 如何交替获得 CPU

## 环境

- Visual Studio Code
- CMake + Ninja
- MinGW GCC
- FreeRTOS Kernel `V11.3.1`
- FreeRTOS 官方 `MSVC_MINGW` Windows 模拟移植层

这个程序运行在 Windows 模拟器中，适合学习 Task 和调度概念。它不能代表 MCU 上的真实实时性能或精确时序。

## 在 VS Code 中运行

1. 在 VS Code 中打开本目录 `freertos/task-basics-lab`。
2. 按 `Ctrl+Shift+P`，选择 `Tasks: Run Task`。
3. 选择 `FreeRTOS: Run`。

首次配置会下载固定版本的 FreeRTOS Kernel。当前 VS Code 任务使用本机 Clash 代理 `127.0.0.1:7897`；如果代理端口变化，需要同步修改 `.vscode/tasks.json`。

也可以分别运行：

- `FreeRTOS: Configure`
- `FreeRTOS: Build`
- `FreeRTOS: Run`
- `FreeRTOS: Test`

按 `F5` 并选择 `Debug FreeRTOS Task Lab` 可以使用 GDB 调试。

## 观察重点

程序创建三个 Task：

| Task | 优先级 | 行为 |
|---|---:|---|
| `MONITOR` | 3 | 检查两个实验 Task 是否达到目标次数，然后结束模拟程序 |
| `HIGH` | 2 | 打印一次，然后延时 300 ms |
| `LOW` | 1 | 打印一次，然后延时 500 ms |

重点观察：高优先级 Task 进入 Blocked 后，低优先级 Task 才有机会运行。优先级高不代表它会一直占用 CPU；是否处于 Ready 状态同样重要。

`MONITOR` 达成测试条件后会调用 `exit()` 结束 Windows 模拟程序，这只是为了让本实验能够自动验证。在真正的 MCU 程序中，不应把退出整个进程当作结束 Task 的常规方式。

## 参考资料

- [FreeRTOS Kernel 的 CMake 使用方式](https://github.com/FreeRTOS/FreeRTOS-Kernel#consume-with-cmake)
- [FreeRTOS Task states](https://www.freertos.org/Documentation/02-Kernel/02-Kernel-features/01-Tasks-and-co-routines/02-Task-states)
- [FreeRTOS xTaskCreate](https://www.freertos.org/Documentation/02-Kernel/04-API-references/01-Task-creation/01-xTaskCreate)
