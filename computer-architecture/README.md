# `computer-architecture/README.md`

# Computer Architecture Learning

本目录用于记录计算机组成原理与计算机系统底层知识。

## Learning Goal

目标是回答一个核心问题：

> 一段 C / C++ 程序最终到底是如何被 CPU 执行的？

并将计算机组成原理与：

* C / C++
* MCU
* RTOS
* Linux
* Performance Optimization

逐渐连接起来。

## Topics

计划学习：

### Data Representation

* Binary
* Hexadecimal
* Signed / Unsigned
* Integer
* Floating Point

### CPU

* Register
* ALU
* Control Unit
* Program Counter
* Instruction

### Instruction Cycle

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

### Pipeline

```text
IF → ID → EX → MEM → WB
```

包括：

* Pipeline
* Data Hazard
* Control Hazard

### Cache

* Cache Line
* Locality
* Cache Hit
* Cache Miss
* Spatial Locality
* Temporal Locality

### Memory

```text
Register
 ↓
Cache
 ↓
RAM
 ↓
Storage
```

### I/O

重点理解：

```text
Polling
vs
Interrupt
vs
DMA
```

## Experiments

本目录不仅记录理论，也尽量通过代码实验理解系统行为。

例如：

* Cache Friendly Array Access
* Memory Access Benchmark
* Stack / Heap Experiment
* Data Alignment
* Bit Operation

目标是将抽象知识变成可以观察到的程序行为。



