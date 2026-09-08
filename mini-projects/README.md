---

# `mini-projects/README.md`

# Mini Projects

本目录用于存放学习过程中完成的小型工程项目。

## Purpose

Mini Project 的作用不是“做很多项目”，而是：

> 将几个独立知识点连接起来。

单独学习：

```text
HSV
Threshold
Morphology
Contour
```

只是知识点。

组合之后：

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

才开始变成一个真正的小项目。

## Planned Projects

### OpenCV Color Detector

目标：

识别指定颜色目标并实时绘制 Bounding Box。

涉及：

* HSV
* Threshold
* Morphology
* Contour
* VideoCapture

---

### OpenCV Object Tracker

目标：

实现简单实时目标跟踪。

涉及：

* Camera
* Detection
* Tracking
* FPS

---

### FreeRTOS Sensor System

结构：

```text
Sensor Task
     ↓
   Queue
     ↓
Processing Task
     ↓
Communication Task
```

涉及：

* Task
* Queue
* Semaphore / Mutex
* Event

---

### Cache Performance Test

通过不同内存访问方式观察 Cache 对程序性能的影响。

涉及：

* C / C++
* Cache
* Locality
* Performance

## Project Requirement

一个 Mini Project 尽量包含：

```text
README.md
src/
assets/
result/
```

README 至少解释：

* 项目做什么
* 为什么做
* 使用什么技术
* 如何运行
* 项目结构
* 实验结果
* 遇到的问题
* 后续改进

## Promotion Rule

当一个 Mini Project：

* 功能足够完整
* 工程规模扩大
* 有独立展示价值
* 能够写进简历

就从这里迁移出去，建立独立 GitHub Repository。

---
