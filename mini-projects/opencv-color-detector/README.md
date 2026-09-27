# OpenCV 蓝色区域检测练习

这是一个使用 OpenCV 4.12.0 和 C++17 编写的静态图像处理练习。程序从图片中分割蓝色区域，清理二值掩膜中的小噪声，提取轮廓，并为面积达到阈值的区域绘制外接矩形和中心点。

## 处理流程

```text
读取 BGR 图片
      ↓
转换为灰度图并保存
      ↓
BGR → HSV
      ↓
inRange() 提取蓝色像素
      ↓
MORPH_OPEN 清理小噪声
      ↓
findContours() 提取外轮廓
      ↓
contourArea() 过滤小区域
      ↓
boundingRect() + circle() 标注目标
```

默认参数位于 `DetectionSettings`：

| 参数 | 默认值 | 作用 |
| --- | --- | --- |
| HSV 下界 | `(90, 80, 50)` | 蓝色范围的最低色相、饱和度和明度 |
| HSV 上界 | `(140, 255, 255)` | 蓝色范围的最高色相、饱和度和明度 |
| 形态学核 | `5 × 5` 矩形 | 开运算使用的邻域大小 |
| 最小轮廓面积 | `5000` | 只有达到该面积的轮廓才绘制方框和中心点 |

这些值适合当前练习图片，但不是适用于所有图片的固定答案。光照、相机白平衡和目标颜色发生变化时，HSV 范围通常也需要重新调整。

## 项目结构

```text
mini-project/
├── include/mini_project/
│   └── blue_object_detector.hpp   # 处理参数、返回结果和公开接口
├── src/
│   ├── blue_object_detector.cpp   # HSV 分割、形态学和轮廓检测
│   └── main.cpp                   # 命令行、图片读写和窗口显示
├── tests/
│   └── blue_object_detector_test.cpp
├── .vscode/                       # VS Code 构建与调试配置
├── CMakeLists.txt
├── CMakePresets.json
└── vcpkg.json
```

图像处理逻辑与窗口、路径和文件输出分离，因此测试可以直接构造一张合成图片，不需要访问个人文件，也不会被 `waitKey(0)` 阻塞。

## 环境

- Windows x64
- Visual Studio 2022 Build Tools（MSVC）
- CMake 3.21 或更高版本
- vcpkg，且已设置环境变量 `VCPKG_ROOT`
- VS Code（可选）
- OpenCV（由 `vcpkg.json` 安装；本次验证版本为 4.12.0）

## 配置、构建与测试

在 PowerShell 中进入项目目录后执行：

```powershell
cmake --preset windows-msvc
cmake --build --preset windows-debug
ctest --test-dir build -C Debug --output-on-failure
```

第一次配置时，vcpkg 可能需要下载和编译 OpenCV，因此耗时会明显长于后续构建。

## 运行

```powershell
.\build\Debug\mini-project.exe "C:\path\to\input.png"
```

也可以指定输出目录：

```powershell
.\build\Debug\mini-project.exe "C:\path\to\input.png" "result"
```

程序默认显示三个窗口，并在 `output/` 中生成：

- `grayscale.png`：灰度图；
- `blue_mask.png`：经过开运算的蓝色二值掩膜；
- `annotated.png`：带轮廓、外接矩形和中心点的结果图。

自动化运行时可加 `--no-gui`，只生成文件而不打开窗口：

```powershell
.\build\Debug\mini-project.exe "C:\path\to\input.png" output --no-gui
```

在 VS Code 中按 `Ctrl+Shift+B` 会通过 CMake 构建；按 `F5` 时会提示输入图片的完整路径，然后启动调试。

## 核心接口说明

### `cv::imread()` / `cv::imwrite()`

`imread()` 把图片文件解码为 `cv::Mat`。读取失败时会得到空矩阵，所以程序在继续处理前调用 `empty()` 检查。`imwrite()` 根据输出文件的扩展名选择编码格式，并返回写入是否成功。

### `cv::cvtColor()`

程序做了两种颜色空间转换：

- `COLOR_BGR2GRAY`：生成单通道灰度结果；
- `COLOR_BGR2HSV`：为按颜色范围分割蓝色区域做准备。

OpenCV 默认按 BGR 顺序读取彩色图片，因此这里使用 `BGR2...`，不是 `RGB2...`。

### `cv::inRange()`

`inRange()` 会逐像素判断 HSV 三个分量是否都落在上下界之间。满足条件的像素在掩膜中变为白色，不满足条件的像素变为黑色。

### `cv::morphologyEx(..., MORPH_OPEN, ...)`

开运算等价于先腐蚀、再膨胀。这里使用 `5 × 5` 矩形核，目的是减少掩膜中尺寸较小的白色噪点。核越大，能消除的白色区域通常越大，但也更容易损伤真实目标。

### `cv::findContours()`

- `RETR_EXTERNAL`：只提取最外层轮廓；
- `CHAIN_APPROX_SIMPLE`：压缩直线段上的冗余点，减少轮廓数据量。

程序先记录所有外轮廓，再使用 `contourArea()` 做面积过滤。面积不足 `5000` 的轮廓仍会显示轮廓线，但不会得到外接矩形和中心点。

### `cv::boundingRect()` / `cv::rectangle()` / `cv::circle()`

`boundingRect()` 计算与图像坐标轴平行的外接矩形。程序使用矩形的左上角、宽和高计算中心点，再分别用绿色矩形和红色实心圆标出检测结果。

## 官方资料

- [OpenCV 4.12.0：图像文件读写](https://docs.opencv.org/4.12.0/d4/da8/group__imgcodecs.html)
- [OpenCV 4.x：使用 HSV 和 inRange 进行阈值分割](https://docs.opencv.org/4.x/da/d97/tutorial_threshold_inRange.html)
- [OpenCV 4.12.0：形态学开运算等变换](https://docs.opencv.org/4.12.0/d3/dbe/tutorial_opening_closing_hats.html)
- [OpenCV 4.12.0：轮廓入门](https://docs.opencv.org/4.12.0/d4/d73/tutorial_py_contours_begin.html)
- [OpenCV 4.x：轮廓外接矩形与圆](https://docs.opencv.org/4.x/da/d0c/tutorial_bounding_rects_circles.html)
- [Microsoft Learn：MSVC `/utf-8` 编译选项](https://learn.microsoft.com/zh-cn/cpp/build/reference/utf-8-set-source-and-executable-character-sets-to-utf-8?view=msvc-170)
