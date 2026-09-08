# Engineering Learning Roadmap

> 个人工程技术学习路线图
> 当前阶段：大三上 · 2026 Fall
> 当前重点：**Embedded Systems / FreeRTOS / OpenCV / Computer Architecture**

---

# 1. Current Goal

本阶段的核心目标不是尽可能多地学习技术，而是逐渐建立一条相对完整的工程能力主线：

**C / C++**
↓
**Computer Architecture**
↓
**MCU / Embedded Systems**
↓
**FreeRTOS**
↓
**Computer Vision / OpenCV**
↓
**Embedded Vision Project**

与此同时，对 **Radar / Signal Processing** 进行低成本探索，用于判断未来考研和研究方向。

---

# 2. Current Priorities

当前优先级：

1. **寻找嵌入式 / 视觉相关实习**
2. **学习 FreeRTOS**
3. **学习 OpenCV**
4. **补充计算机组成原理**
5. **持续强化 C / C++**
6. **探索 Radar**
7. **完成 Embedded Vision Project**

当前阶段原则：

* 不追求同时学习大量技术
* 不为了“学完课程”而学习
* 每个知识点尽量通过代码和实验验证
* 优先完成能够形成项目成果的内容
* 学习内容尽量服务于实习和未来研究方向

---

# 3. OpenCV Roadmap

目标：

> 掌握经典计算机视觉的基本处理流程，能够独立完成简单实时视觉程序，并为后续视觉算法学习建立基础。

## Stage 1 — Image Basics

* [ ] 图像读取 `imread`
* [ ] 图像显示 `imshow`
* [ ] 图像保存 `imwrite`
* [ ] `Mat` 基本结构
* [ ] Pixel 基本概念
* [ ] Resize
* [ ] Crop
* [ ] 图像通道
* [ ] BGR / RGB
* [ ] Grayscale
* [ ] HSV

### Mini Project

* [ ] Basic Image Processor

实现：

```text
Image
 ↓
Resize
 ↓
Crop
 ↓
Color Conversion
 ↓
Save
```

---

## Stage 2 — Image Segmentation

* [ ] Threshold
* [ ] Binary Image
* [ ] HSV Threshold
* [ ] Mask

理解：

* 阈值为什么能够进行目标分割
* HSV 相比 RGB 为什么更适合部分颜色识别任务
* 光照变化会如何影响分割结果

### Mini Project

* [ ] HSV Color Detector

```text
Camera / Image
      ↓
     HSV
      ↓
  Threshold
      ↓
     Mask
```

---

## Stage 3 — Image Filtering

* [ ] Gaussian Blur
* [ ] Median Blur
* [ ] Noise
* [ ] Kernel 基本概念

理解：

* 图像滤波的目的
* Gaussian 与 Median 的区别
* 为什么图像处理通常需要先进行降噪

---

## Stage 4 — Morphology

* [ ] Erosion
* [ ] Dilation
* [ ] Opening
* [ ] Closing

理解：

* 腐蚀 / 膨胀对目标区域的影响
* Morphology 在目标检测前处理中的作用

---

## Stage 5 — Edge Detection

* [ ] Gradient
* [ ] Sobel
* [ ] Canny

理解：

* 图像边缘是什么
* Gradient 与边缘的关系
* Canny 的基本流程
* Threshold 参数对结果的影响

---

## Stage 6 — Contour

* [ ] `findContours`
* [ ] Contour Area
* [ ] Perimeter
* [ ] Bounding Rectangle
* [ ] Rotated Rectangle
* [ ] Object Filtering

### Mini Project

* [ ] Color Object Detector

```text
Camera
 ↓
HSV
 ↓
Threshold
 ↓
Morphology
 ↓
Contour
 ↓
Bounding Box
```

目标：

能够在实时图像中找到指定颜色目标并绘制 Bounding Box。

---

## Stage 7 — Video Processing

* [ ] `VideoCapture`
* [ ] Camera Input
* [ ] Video Input
* [ ] Frame Processing
* [ ] FPS
* [ ] Latency

目标：

将前面的静态图像算法改造成实时视觉程序。

---

## Stage 8 — Feature

了解：

* [ ] Feature Point
* [ ] ORB
* [ ] Feature Descriptor
* [ ] Feature Matching
* [ ] Template Matching

当前阶段只要求理解基本思想，不进行过度深入。

---

# 4. FreeRTOS Roadmap

目标：

> 从“会使用 MCU”逐渐进入“理解嵌入式系统如何组织多个任务”。

---

## Stage 1 — Task

* [ ] Task 基本概念
* [ ] `xTaskCreate`
* [ ] Task Function
* [ ] Task State
* [ ] Running
* [ ] Ready
* [ ] Blocked
* [ ] Suspended

### Experiment

创建三个 Task：

```text
Task_LED
Task_Sensor
Task_Print
```

观察不同 Task 的运行情况。

---

## Stage 2 — Scheduler

* [ ] Scheduler
* [ ] Tick
* [ ] Context Switch
* [ ] Priority
* [ ] Preemption
* [ ] `vTaskDelay`

理解：

> FreeRTOS 为什么能够让一个 MCU 看起来“同时运行多个任务”。

---

## Stage 3 — Queue

* [ ] Queue
* [ ] `xQueueSend`
* [ ] `xQueueReceive`
* [ ] Producer / Consumer

### Experiment

```text
Sensor Task
     ↓
   Queue
     ↓
Processing Task
```

理解：

> 为什么不同 Task 之间不应该总通过全局变量通信。

---

## Stage 4 — Semaphore

* [ ] Binary Semaphore
* [ ] Counting Semaphore
* [ ] Task Synchronization

理解：

> Semaphore 解决的是哪一类问题。

---

## Stage 5 — Mutex

* [ ] Mutex
* [ ] Shared Resource
* [ ] Race Condition
* [ ] Critical Section
* [ ] Priority Inversion

### Experiment

两个 Task 同时访问 UART / Shared Resource。

观察没有保护时可能发生的问题。

---

## Stage 6 — Event Group

* [ ] Event
* [ ] Event Bit
* [ ] Event Group

理解：

> Event Group 与 Queue / Semaphore 的区别。

---

## Stage 7 — Software Timer

* [ ] Software Timer
* [ ] Periodic Timer
* [ ] One-shot Timer

---

## Stage 8 — Interrupt

* [ ] Interrupt
* [ ] ISR
* [ ] Task
* [ ] Queue From ISR
* [ ] Semaphore From ISR

重点理解：

```text
Hardware Interrupt
        ↓
       ISR
        ↓
      Queue
        ↓
      Task
```

---

## Stage 9 — Memory

* [ ] Stack
* [ ] Heap
* [ ] Dynamic Allocation
* [ ] Static Allocation
* [ ] Stack Overflow
* [ ] Heap Usage

理解：

> 为什么 MCU 上的内存管理比 PC 程序更加重要。

---

## Stage 10 — Reliability

* [ ] Watchdog
* [ ] Timeout
* [ ] Error Handling
* [ ] Runtime Statistics
* [ ] Stack Monitoring

最终目标：

能够设计一个简单的多任务嵌入式系统。

---

# 5. Computer Architecture Roadmap

目标：

> 理解程序从代码变成 CPU 执行过程中的关键机制，为嵌入式、操作系统和性能优化建立底层认知。

---

## Stage 1 — Data Representation

* [ ] Binary
* [ ] Hexadecimal
* [ ] Signed / Unsigned
* [ ] Integer Representation
* [ ] Floating Point 基本概念

---

## Stage 2 — CPU

* [ ] CPU 基本结构
* [ ] Register
* [ ] ALU
* [ ] Control Unit
* [ ] Program Counter
* [ ] Instruction

---

## Stage 3 — Instruction Cycle

理解：

```text
Fetch
 ↓
Decode
 ↓
Execute
 ↓
Memory
 ↓
Write Back
```

* [ ] Fetch
* [ ] Decode
* [ ] Execute

---

## Stage 4 — Pipeline

* [ ] Pipeline
* [ ] IF
* [ ] ID
* [ ] EX
* [ ] MEM
* [ ] WB
* [ ] Data Hazard
* [ ] Control Hazard

目标：

理解现代 CPU 为什么使用流水线。

---

## Stage 5 — Cache

* [ ] Cache
* [ ] Cache Line
* [ ] Locality
* [ ] Spatial Locality
* [ ] Temporal Locality
* [ ] Cache Hit
* [ ] Cache Miss

### Experiment

比较不同二维数组访问顺序的执行速度。

目标：

从代码层面观察 Cache 对性能的影响。

---

## Stage 6 — Memory Hierarchy

理解：

```text
Register
   ↓
Cache
   ↓
RAM
   ↓
Storage
```

* [ ] Register
* [ ] Cache
* [ ] SRAM
* [ ] DRAM
* [ ] Storage

---

## Stage 7 — I/O

* [ ] Memory Mapped I/O
* [ ] Polling
* [ ] Interrupt
* [ ] DMA

重点理解：

```text
Polling
vs
Interrupt
vs
DMA
```

以及三种方式分别适用于什么场景。

---

# 6. C / C++ Roadmap

当前 C / C++ 不单独作为主要学习方向，而是作为：

> OpenCV + Embedded + RTOS 的基础能力。

---

## C

重点：

* [ ] Pointer
* [ ] Array
* [ ] Function Pointer
* [ ] Struct
* [ ] Memory
* [ ] `const`
* [ ] `static`
* [ ] `volatile`
* [ ] Bit Operation
* [ ] Macro
* [ ] Header File
* [ ] Compilation

嵌入式重点：

* [ ] Pointer
* [ ] Memory
* [ ] `volatile`
* [ ] Bit Operation
* [ ] Struct
* [ ] Function Pointer

---

## C++

重点：

* [ ] Reference
* [ ] Class
* [ ] Constructor
* [ ] Destructor
* [ ] Inheritance
* [ ] Polymorphism
* [ ] Virtual Function
* [ ] STL
* [ ] `vector`
* [ ] `map`
* [ ] Smart Pointer
* [ ] RAII
* [ ] Modern C++ 基础

当前阶段优先满足：

> 能够阅读和编写 OpenCV C++ 程序。

---

# 7. Radar Exploration Roadmap

当前定位：

> **探索方向，而不是主线。**

目标：

在本学期结束前回答：

> 我是否愿意未来研究 Radar / Signal Processing？

---

## Stage 1 — Radar Basics

* [ ] Radar 是什么
* [ ] Radar System 基本组成
* [ ] Transmitter
* [ ] Receiver
* [ ] Antenna
* [ ] Echo

---

## Stage 2 — Ranging

* [ ] Time of Flight
* [ ] Distance Measurement
* [ ] Radar Equation 基本概念

---

## Stage 3 — Doppler

* [ ] Doppler Effect
* [ ] Velocity Measurement

理解：

> 为什么目标运动会产生频率变化。

---

## Stage 4 — FMCW

* [ ] FMCW
* [ ] Chirp
* [ ] Frequency Sweep
* [ ] Beat Frequency

理解：

```text
Transmit Chirp
      ↓
Target Reflection
      ↓
Received Chirp
      ↓
Mixing
      ↓
Beat Frequency
      ↓
Distance
```

---

## Stage 5 — FFT

* [ ] Time Domain
* [ ] Frequency Domain
* [ ] FFT
* [ ] Spectrum

目标：

理解 FFT 为什么能够从信号中提取目标信息。

---

## Stage 6 — Range Doppler

* [ ] Range FFT
* [ ] Doppler FFT
* [ ] Range-Doppler Map

---

## Stage 7 — Detection

了解：

* [ ] CFAR
* [ ] Angle Estimation

当前阶段不要求深入推导。

---

# 8. Embedded Vision Project

长期项目目标：

> 将 OpenCV、RTOS、Embedded System 等知识逐渐连接成一个完整工程。

---

## Project V0.1

目标：

完成系统设计。

```text
Camera
   ↓
Image Input
   ↓
OpenCV Processing
   ↓
Target Detection
   ↓
Result
```

---

## Project V0.5

加入：

```text
Sensor Task
Vision Task
Communication Task
UI Task
```

使用：

* Queue
* Event
* Mutex

进行 Task 之间通信。

---

## Project V1.0

最终至少包含：

* [ ] Working Code
* [ ] Git Repository
* [ ] README
* [ ] Architecture Diagram
* [ ] Demo Video
* [ ] Technical Stack
* [ ] Problems & Solutions
* [ ] Performance Test

目标：

成为能够展示给面试官的完整项目。

---

# 9. Internship Preparation

技术学习最终需要服务于实习。

重点准备：

## Embedded

* [ ] C
* [ ] Pointer
* [ ] Memory
* [ ] MCU
* [ ] Interrupt
* [ ] UART
* [ ] SPI
* [ ] I2C
* [ ] FreeRTOS

## C++

* [ ] Pointer / Reference
* [ ] Class
* [ ] Virtual Function
* [ ] STL
* [ ] Smart Pointer
* [ ] Memory Management

## Computer System

* [ ] CPU
* [ ] Cache
* [ ] Memory
* [ ] Interrupt
* [ ] DMA

## Computer Vision

* [ ] OpenCV
* [ ] Image Processing
* [ ] Contour
* [ ] Video Processing

---

# 10. 8-Week Milestones

## Week 1

目标：

* [ ] 建立代码学习仓库
* [ ] OpenCV 环境搭建
* [ ] OpenCV 基础图像操作
* [ ] FreeRTOS 环境搭建
* [ ] Resume V1
* [ ] 建立 Internship JD Pool

---

## Week 2

目标：

* [ ] OpenCV Color Space
* [ ] HSV Color Detection
* [ ] FreeRTOS Task
* [ ] Scheduler
* [ ] Priority
* [ ] CPU 基本结构

---

## Week 3

目标：

* [ ] OpenCV Blur / Canny
* [ ] Contour
* [ ] FreeRTOS Queue
* [ ] Semaphore
* [ ] Mutex
* [ ] Instruction Cycle

完成：

* [ ] Vision Demo V0.1

---

## Week 4

目标：

* [ ] OpenCV VideoCapture
* [ ] Real-time Vision
* [ ] FreeRTOS Event Group
* [ ] Timer
* [ ] Interrupt
* [ ] Pipeline
* [ ] FMCW Radar Basics

启动：

* [ ] Embedded Vision Project V0.1

---

## Week 5

目标：

* [ ] OpenCV Feature Basics
* [ ] FreeRTOS Memory
* [ ] Stack / Heap
* [ ] Cache
* [ ] Embedded Vision Code Refactor
* [ ] Radar FFT Basics

---

## Week 6

目标：

* [ ] RTOS System Architecture
* [ ] Watchdog
* [ ] Error Handling
* [ ] Real-time Vision
* [ ] FPS / Latency
* [ ] Memory Hierarchy
* [ ] Range-Doppler Basics

完成：

* [ ] Vision Project V0.5

---

## Week 7

目标：

* [ ] FreeRTOS Knowledge Map
* [ ] OpenCV Review
* [ ] Interrupt / DMA
* [ ] Embedded Interview Questions
* [ ] Project Presentation
* [ ] Resume V2

---

## Week 8

目标：

* [ ] FreeRTOS Review
* [ ] OpenCV Mini Project
* [ ] Computer Architecture Review
* [ ] Project Refactor
* [ ] README
* [ ] Architecture Diagram
* [ ] Demo Video

完成：

* [ ] Embedded Vision Project V1.0

---

# 11. Learning Workflow

每次学习尽量遵循：

```text
Understand
    ↓
Code
    ↓
Run
    ↓
Experiment
    ↓
Break It
    ↓
Debug
    ↓
Explain
    ↓
Document
    ↓
Commit
```

具体执行：

1. 了解概念
2. 自己写代码
3. 成功运行
4. 修改参数观察变化
5. 主动制造错误
6. Debug
7. 用自己的语言解释
8. 写 README / Notes
9. Git Commit

---

# 12. Repository Rules

这个仓库只保存：

* 我真正学过的内容
* 我真正运行过的代码
* 我真正做过的实验
* 我自己的理解
* 我踩过的坑
* 我完成的项目

尽量避免：

* 大量复制教程
* 收藏但没有阅读的资料
* 完全没有运行过的代码
* 为了 GitHub Contribution 而无意义 Commit
* 大量半途而废的小 Repo

---

# 13. Not Now

以下内容不是当前阶段重点：

* Deep Learning 深入
* YOLO 深入
* ROS
* Linux Kernel
* Linux Driver 深入
* CUDA
* Complex Radar Algorithm
* SLAM
* Reinforcement Learning

不是永远不学，而是：

> **Not Now.**

等当前主线完成后再决定是否进入。

---

# 14. Current Focus

## September 2026

当前只关注：

### Main

* [ ] Internship
* [ ] OpenCV Basics
* [ ] FreeRTOS Basics

### Secondary

* [ ] Computer Architecture
* [ ] C / C++

### Exploration

* [ ] Radar Fundamentals

---

# 15. Long-Term Direction

希望最终逐渐形成：

```text
Embedded Systems
       +
Computer Vision
       +
System Knowledge
       ↓
Embedded Vision Engineer
```

同时通过 Radar 学习判断未来是否进一步进入：

```text
Radar
+
Signal Processing
+
Computer Vision
```

相关研究方向。

---

# 16. Reminder

学习路线不是固定课程表。

Roadmap 的作用不是要求所有内容全部完成，而是始终知道：

> **我现在在哪里？**

> **我为什么学习这个？**

> **下一步应该做什么？**

当新的技术出现时，不立即加入学习计划。

先判断：

> 它是否服务于当前目标？

如果不是：

**先放入 Backlog，而不是立刻开始。**

