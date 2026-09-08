---

# `cpp/README.md`

# C / C++ Learning

本目录用于记录 C / C++ 学习和工程实践。

当前 C / C++ 的定位不是单独刷完整语言课程，而是作为：

> Embedded Systems + OpenCV + Algorithm Development

的基础能力。

## C Focus

重点包括：

* Pointer
* Array
* Struct
* Function Pointer
* Memory
* Stack / Heap
* `const`
* `static`
* `volatile`
* Macro
* Bit Operation
* Header File
* Compilation

尤其关注嵌入式开发中高频使用的：

```text
Pointer
Memory
volatile
Bit Operation
Struct
Function Pointer
```

## C++ Focus

重点包括：

* Reference
* Class
* Constructor
* Destructor
* Inheritance
* Polymorphism
* Virtual Function
* STL
* vector
* map
* Smart Pointer
* RAII
* Modern C++

当前阶段首先达到：

> 能够阅读、理解并编写 OpenCV C++ 程序。

## Pitfalls

计划专门记录容易出问题的内容：

```text
dangling pointer
memory leak
array vs pointer
const pointer
sizeof
virtual destructor
object lifetime
```

这些内容同时作为未来实习面试的复习资料。

## Principle

不要只记录语法。

更关注：

> 内存发生了什么？

> 对象什么时候创建和销毁？

> 指针到底指向哪里？

> 为什么会产生 Undefined Behavior？

---

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


