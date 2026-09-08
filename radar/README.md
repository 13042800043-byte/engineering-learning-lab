---

# `radar/README.md`

# Radar Learning

本目录用于记录雷达与信号处理基础知识。

当前 Radar 的定位是：

> Exploration Track

即探索方向，而不是当前技术主线。

## Goal

本学期希望回答：

> 我是否真正对 Radar / Signal Processing 感兴趣？

> 是否愿意在研究生阶段继续深入这个方向？

因此当前阶段以建立基本认知为主，不急于深入复杂数学推导。

## Topics

计划了解：

### Radar Basics

* Radar System
* Transmitter
* Receiver
* Antenna
* Echo

### Ranging

* Time of Flight
* Distance Measurement
* Radar Equation

### Doppler

* Doppler Effect
* Velocity Measurement

### FMCW

* Chirp
* Frequency Sweep
* Beat Frequency

基本过程：

```text
Transmit Chirp
      ↓
Target
      ↓
Echo
      ↓
Mixing
      ↓
Beat Frequency
      ↓
Distance
```

### Signal Processing

* Time Domain
* Frequency Domain
* FFT
* Spectrum

### Radar Processing

* Range FFT
* Doppler FFT
* Range-Doppler Map
* CFAR
* Angle Estimation

## Simulation

后续计划使用：

* Python
* MATLAB

做简单雷达信号处理仿真。

学习目标不是只知道公式，而是逐渐理解：

> Signal → Processing → Information

这条链路。

