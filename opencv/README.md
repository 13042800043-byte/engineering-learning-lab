# `opencv/README.md`

# OpenCV Learning

本目录用于记录我的 OpenCV / Computer Vision 学习过程，包括基础图像处理、目标提取、轮廓检测、视频处理以及后续的小型视觉项目。

## Learning Goal

当前目标不是单纯记忆 OpenCV API，而是理解一套完整的经典视觉处理流程：

```text
Image / Camera
      ↓
Preprocessing
      ↓
Segmentation
      ↓
Feature Extraction
      ↓
Object Detection
      ↓
Result Visualization
```

最终希望能够独立完成简单的实时视觉程序，并为后续嵌入式视觉、目标检测和更深入的视觉算法学习建立基础。

## Topics

计划学习：

* Image I/O
* Mat
* Resize / Crop
* Color Space
* Grayscale
* HSV
* Threshold
* Image Filtering
* Morphology
* Edge Detection
* Contour
* Bounding Box
* VideoCapture
* Feature Point
* Feature Matching
* FPS / Latency

## Directory Structure

```text
opencv/
├── 01_basic_image/
├── 02_color_space/
├── 03_threshold/
├── 04_filter/
├── 05_morphology/
├── 06_edge/
├── 07_contour/
├── 08_feature/
├── 09_video/
└── exercises/
```

每个知识点尽量包含：

* 可运行代码
* 实验结果
* 参数测试
* 学习笔记
* 遇到的问题
* 自己的理解

## Learning Principle

学习 OpenCV 时尽量遵循：

```text
Understand
   ↓
Code
   ↓
Run
   ↓
Change Parameters
   ↓
Observe
   ↓
Explain
```

重点不是：

> “这个函数怎么写？”

而是：

> “这个算法解决什么问题？”

> “为什么这样处理？”

> “参数变化会产生什么结果？”
