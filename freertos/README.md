---

# `freertos/README.md`

# FreeRTOS Learning

本目录用于记录 FreeRTOS 学习、实验以及嵌入式多任务系统设计。

## Learning Goal

从单线程 MCU 程序逐渐过渡到理解：

> 一个嵌入式系统如何组织多个任务，以及不同任务之间如何进行同步、通信和资源管理。

最终希望能够独立设计一个较完整的 FreeRTOS 多任务系统。

## Topics

计划学习：

* Task
* Task State
* Scheduler
* Priority
* Context Switch
* Tick
* Queue
* Semaphore
* Mutex
* Critical Section
* Event Group
* Software Timer
* Interrupt
* ISR
* Memory Management
* Stack / Heap
* Watchdog
* Error Handling

## Core Architecture

希望逐渐能够设计类似：

```text
Sensor Task
     │
     ↓
   Queue
     │
     ↓
Processing Task
     │
     ↓
Communication Task
     │
     ↓
   Cloud / UI
```

## Learning Focus

学习每一种 RTOS 机制时，需要回答：

1. 它解决什么问题？
2. 如果不用它，会发生什么？
3. 它和其他机制有什么区别？
4. 什么情况下应该使用？
5. 有没有资源或性能代价？

例如：

```text
Queue
vs
Global Variable
```

```text
Semaphore
vs
Mutex
```

```text
Polling
vs
Interrupt
```

## Goal

最终能够把 FreeRTOS 与：

* MCU
* Sensor
* Communication
* OpenCV / Vision
* Embedded Project

结合，而不仅仅停留在 API 使用层面。


