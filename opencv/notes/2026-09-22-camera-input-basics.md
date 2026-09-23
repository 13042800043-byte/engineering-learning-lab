# OpenCV 摄像头读取与显示

> 实践日期：2026-09-22
>
> 源码复盘：2026-09-23
>
> 记录状态：已根据实际操作和后续问答整理

## 本次实际完成

- 参考课程示例，亲手输入了一份 OpenCV C++ 摄像头程序。
- 成功编译并运行程序，在 `Video` 窗口中看到了实时摄像头画面。
- 本次只测试了摄像头输入，没有测试视频文件输入。

## 程序执行流程

```text
解析命令行参数
       ↓
没有提供视频文件路径
       ↓
打开编号为 0 的摄像头
       ↓
检查摄像头是否成功打开
       ↓
循环读取一帧图像
       ↓
在窗口中显示这一帧
       ↓
处理窗口刷新和键盘事件
       ↓
按下任意键后退出循环并释放摄像头
```

实时视频并不是一种与图片完全不同的数据。摄像头会持续提供一帧帧图像，程序不断读取并快速显示这些图像，于是形成连续的视频效果。

## 本次接触的类与函数

### 1. `cv::CommandLineParser`

```cpp
cv::CommandLineParser parser(argc, argv, keys);
```

它用于解析启动程序时传入的命令行参数：

- `argc` 表示参数数量；
- `argv` 保存每个参数的文本；
- `keys` 描述程序支持哪些参数以及参数的默认值。

示例代码还使用了以下接口：

```cpp
parser.has("help");
parser.printMessage();
parser.get<cv::String>(0);
parser.check();
parser.printErrors();
```

- `has("help")`：检查是否传入帮助参数；
- `printMessage()`：输出参数使用说明；
- `get<cv::String>(0)`：取得第一个位置参数，在本程序中代表视频文件路径；
- `check()`：检查参数解析是否有效；
- `printErrors()`：输出参数解析错误。

本次没有传入视频路径，因此得到的 `videoFile` 为空，程序进入摄像头分支。

### 2. `cv::VideoCapture`

```cpp
cv::VideoCapture cap;
```

`VideoCapture` 用来管理视频输入源。输入源可以是摄像头，也可以是视频文件。刚创建 `cap` 时，它还没有连接到任何输入源。

### 3. `VideoCapture::open()`

```cpp
cap.open(0);
cap.open(videoFile);
```

这两个调用名称相同，但参数类型不同，属于 C++ 函数重载：

- `open(int)` 接收整数，整数表示摄像头编号；
- `open(const cv::String&)` 接收字符串，字符串表示视频文件路径。

因此，`cap.open(0)` 的含义是打开编号为 `0` 的默认摄像头。它不是把 `0` 当成布尔值，也不是固定的“开启摄像头命令”。

代码中虽然保留了视频文件分支，但本次并未实际测试该分支。

### 4. `VideoCapture::isOpened()`

```cpp
if (!cap.isOpened())
{
    return -1;
}
```

`isOpened()` 用于判断视频输入源是否成功建立连接。它主要检查初始化结果，不能代替循环中每一次取帧的结果检查。

例如，摄像头最初可能成功打开，但运行中仍可能被拔出或发生读取失败。此时应检查每次读取是否成功。

### 5. `cv::Mat`

```cpp
cv::Mat frame;
```

`Mat` 是 OpenCV 保存图像的核心数据结构。本程序中的 `frame` 用来保存当前从摄像头取得的一帧图像。

当前先把 `Mat` 理解为“图像数据及其描述信息的容器”。它不仅保存像素，还管理图像尺寸、通道数、像素类型和底层数据引用。其内存结构和浅拷贝机制尚未在本次实验中深入验证。

### 6. `cap >> frame`

```cpp
cap >> frame;
```

这是 `VideoCapture` 对 `>>` 运算符的重载，用于从当前视频源读取下一帧，并把结果写入 `frame`。

它也可以用更直观的形式表达：

```cpp
bool ok = cap.read(frame);
```

`read()` 的返回值表示本次是否成功取得下一帧。原示例使用了 `cap >> frame`，但没有检查读取失败的情况。

### 7. `cv::namedWindow()`

```cpp
cv::namedWindow("Video", 1);
```

它创建名为 `Video` 的显示窗口。第二个参数是窗口模式标志。为了让代码含义更清楚，可以使用具名常量：

```cpp
cv::namedWindow("Video", cv::WINDOW_AUTOSIZE);
```

### 8. `cv::imshow()`

```cpp
cv::imshow("Video", frame);
```

`imshow()` 把 `frame` 提交给名为 `Video` 的窗口进行显示。它负责提出显示请求，但窗口的刷新和事件处理还需要 `waitKey()` 配合。

### 9. `cv::waitKey()`

```cpp
if (cv::waitKey(30) >= 0)
{
    break;
}
```

`waitKey(30)` 不只是让画面停留约 30 ms，它还负责处理 OpenCV 窗口的刷新和键盘事件：

- 没有检测到按键时，通常返回负数；
- 检测到按键时，返回非负值；
- 当前判断条件意味着按下任意键都会退出循环。

如果直接删除 `waitKey()`，程序不一定会因为运行过快而闪退。更可能出现窗口不能正常刷新、无法响应键盘事件、循环高速占用 CPU，并且失去当前的按键退出条件。

### 10. `VideoCapture::release()`

```cpp
cap.release();
```

`release()` 主动断开视频输入源并释放摄像头资源。即使对象析构时通常也会释放资源，显式调用仍能清楚表达程序在何处结束摄像头使用。

## 源码复盘后确认的理解

1. `open(0)` 和 `open(videoFile)` 的区别来自参数类型不同，编译器会选择不同的重载版本。
2. `cap.read(frame)` 或 `cap >> frame` 负责取图，`imshow()` 负责提交显示请求，`waitKey()` 负责窗口刷新和键盘事件处理。
3. `isOpened()` 检查视频源是否成功打开，`read()` 检查当前这一帧是否成功取得；两者不能相互代替。
4. 删除 `waitKey()` 的主要问题不仅是缺少延时，更重要的是窗口事件无法正常处理。

## 当前示例中发现的不足

原循环没有检查视频结束、摄像头断开或单帧读取失败的情况：

```cpp
cv::Mat frame;

while (cap.read(frame))
{
    if (frame.empty())
    {
        break;
    }

    cv::imshow("Video", frame);

    if (cv::waitKey(30) >= 0)
    {
        break;
    }
}
```

这段代码是复盘时整理出的改进方式，本次记录不声称已经亲手修改并运行验证。

## 尚未完成

- 尚未测试从视频文件读取画面。
- 尚未实际测试摄像头中途断开时的程序行为。
- 尚未亲手加入 `read()` 返回值和空帧检查并运行验证。
- 尚未深入学习 `Mat` 的通道、像素类型、内存布局和拷贝机制。

## 官方参考资料

- [OpenCV 4.12.0：视频输入与 `VideoCapture`](https://docs.opencv.org/4.12.0/d5/dc4/tutorial_video_input_psnr_ssim.html)
- [OpenCV 4.12.0：Video I/O 后端与属性](https://docs.opencv.org/4.12.0/d4/d15/group__videoio__flags__base.html)
- [OpenCV 4.12.0：HighGUI 接口](https://docs.opencv.org/4.12.0/d4/dd5/highgui_8hpp.html)
