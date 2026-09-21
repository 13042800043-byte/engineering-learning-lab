# RTOS 与 Task 入门

> 日期：2026-09-21  
> 学习方式：在 Windows 上观看课程示例  
> 实践状态：尚未配置环境，也没有亲自创建或运行 Task

## 今天接触的内容

- RTOS 的基本作用
- 裸机系统与多任务系统的区别
- 创建 Task 的基本概念
- RTOS 运行时如何调度和切换任务

## 当前理解与澄清

### RTOS 解决什么问题

我最初认为 RTOS 主要解决裸机程序顺序执行造成的资源浪费，并让系统更加稳定、实用。

需要进一步澄清：RTOS 的主要价值是通过调度器管理多个任务，并提供较可预测的响应时间，以及任务通信、同步和资源管理机制。使用 RTOS 并不会自动让系统更稳定，系统稳定性仍然取决于任务设计、优先级、共享资源保护和错误处理。

### 裸机与多任务系统

我最初将两者概括为：裸机程序顺序执行，RTOS 中的任务交叉同时执行。

更准确的理解是：

- 裸机程序也可以通过中断和状态机处理多个事件，不一定只能做简单的顺序执行。
- RTOS 把不同工作组织成任务，由调度器选择当前运行的任务。
- 在单核处理器上，同一时刻通常只有一个 Task 真正在运行；多个任务快速切换，表现得像同时进行。

### Task 创建

目前只知道创建 Task 需要任务函数以及与任务有关的参数，还不能完整说明 `xTaskCreate()` 的参数。

后续需要结合实际代码认识：

```c
xTaskCreate(
    task_function,
    task_name,
    stack_depth,
    task_parameter,
    task_priority,
    task_handle
);
```

这一部分当前属于待实践内容，不能标记为已经掌握。

### 调度与任务状态

我已经注意到优先级会影响调度，但最初认为任务切换需要先经过 `Blocked → Suspended`。

需要纠正：调度器通常从 **Ready** 状态的任务中选择能够运行的任务，优先运行最高优先级的 Ready Task。运行中的任务可能因为更高优先级任务就绪、时间片轮转、主动延时或等待事件而让出 CPU。

- **Running**：正在使用 CPU。
- **Ready**：具备运行条件，正在等待调度。
- **Blocked**：正在等待时间或外部事件，不占用 CPU。
- **Suspended**：被明确挂起，通常需要显式恢复。

任务切换不要求依次经过 Blocked 和 Suspended。Running Task 被抢占后可以回到 Ready；调用延时或等待事件时则可能进入 Blocked。

## 当前薄弱点

- 还不能完整解释 `xTaskCreate()` 的参数。
- 对 Ready、Blocked、Suspended 之间的区别还需要通过运行实验巩固。
- 尚未观察不同优先级和延时设置对任务执行顺序的影响。

## 下一步实践

1. 在 Windows 上配置可运行的 FreeRTOS 学习环境。
2. 创建两个输出不同信息的 Task。
3. 观察 Task 的交替运行现象。
4. 修改优先级与延时时间，比较运行结果。
5. 根据实验重新解释 Ready、Running 和 Blocked 状态。

## 参考资料

- [FreeRTOS：Task states](https://www.freertos.org/Documentation/02-Kernel/02-Kernel-features/01-Tasks-and-co-routines/02-Task-states)
- [FreeRTOS：Implementing a task](https://www.freertos.org/Documentation/02-Kernel/02-Kernel-features/01-Tasks-and-co-routines/05-Implementing-a-task)
- [FreeRTOS：xTaskCreate](https://www.freertos.org/Documentation/02-Kernel/04-API-references/01-Task-creation/01-xTaskCreate)
