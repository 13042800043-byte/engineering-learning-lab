# OpenCV 实时蓝色目标检测

这是一个使用 OpenCV 4.12.0 和 C++17 编写的摄像头颜色检测练习。程序逐帧读取默认摄像头，将图像转换到 HSV 颜色空间，提取蓝色区域，并在实时画面中标注目标外接矩形、矩形中心、轮廓面积、目标数量和近似 FPS。

## 处理流程

```text
打开默认摄像头
      ↓
读取一帧 BGR 图像
      ↓
BGR → HSV
      ↓
inRange() 提取蓝色区域
      ↓
开运算清理小白色噪点
      ↓
闭运算填补目标内部小孔洞
      ↓
提取最外层轮廓
      ↓
按轮廓面积过滤
      ↓
绘制外接矩形、中心坐标和面积
      ↓
显示目标数量与近似 FPS
```

## 当前参数

| 参数 | 当前值 | 作用 |
| --- | --- | --- |
| 摄像头编号 | `0` | 打开系统默认摄像头 |
| 请求分辨率 | `1280 × 720` | 请求摄像头输出尺寸；实际值由摄像头与驱动决定 |
| HSV 下界 | `(100, 80, 50)` | 蓝色范围的最低 H、S、V |
| HSV 上界 | `(130, 255, 255)` | 蓝色范围的最高 H、S、V |
| 形态学核 | `5 × 5` 矩形 | 决定开、闭运算处理的邻域 |
| 最小轮廓面积 | `5000` | 面积不足的轮廓不绘制目标框 |
| 退出键 | `Esc` | 结束实时循环 |

这些参数只适用于当前练习起点，不是通用答案。环境光、摄像头白平衡、目标距离和蓝色深浅发生变化时，HSV 阈值和面积阈值都可能需要调整。

## 核心结果

程序显示两个窗口：

- `Color Target Detector`：原始画面加检测结果；
- `Binary Mask`：完成开、闭运算后的蓝色二值掩膜。

对于通过面积筛选的轮廓，主窗口会显示：

- 绿色外接矩形；
- 红色矩形中心点；
- 中心坐标；
- 轮廓面积；
- 当前目标数量；
- 本轮近似 FPS。

这里的红点是“与坐标轴平行的外接矩形中心”，不一定等于物体的轮廓质心。

## 环境

- Windows x64
- Visual Studio 2022 Build Tools（MSVC）
- CMake 3.21 或更高版本
- vcpkg，且已设置环境变量 `VCPKG_ROOT`
- OpenCV（由 `vcpkg.json` 安装；本次构建使用 4.12.0）
- VS Code、C/C++ 扩展和 CMake Tools 扩展（可选）

## 配置与构建

在 PowerShell 中进入项目目录：

```powershell
cmake --preset windows-msvc
cmake --build --preset windows-debug
```

首次配置时，vcpkg 可能需要下载或编译依赖，因此耗时会明显更长。

## 运行

```powershell
.\build\Debug\opencv-realtime-color-detector.exe
```

在 VS Code 中：

1. 只打开本项目文件夹；
2. 按 `Ctrl+Shift+B` 通过 CMake 构建；
3. 按 `F5` 启动调试；
4. 在 OpenCV 窗口中按 `Esc` 退出。

摄像头打不开时，先检查是否被会议软件、浏览器或另一个 OpenCV 程序占用。

## 关键接口说明

### `cv::VideoCapture`

`VideoCapture(0)` 尝试打开默认摄像头。程序先用 `isOpened()` 检查初始化，再在循环中逐帧检查 `frame.empty()`。两者分别对应“摄像头是否成功打开”和“当前帧是否有效”。

`cap.set()` 只是在向摄像头后端请求属性值。摄像头、驱动或后端不支持时，实际分辨率可能与请求值不同。

### `cv::cvtColor()` 与 `cv::inRange()`

`cvtColor(..., COLOR_BGR2HSV)` 把 BGR 图像转换成 HSV。对于 8 位 HSV 图像，OpenCV 的 H 通道通常使用 `0～179`。

`inRange()` 会逐像素检查 H、S、V 是否都位于上下界之间，生成“蓝色区域为白，其余区域为黑”的二值掩膜。

### `cv::morphologyEx()`

- `MORPH_OPEN`：先腐蚀、再膨胀，适合清理孤立的小白点；
- `MORPH_CLOSE`：先膨胀、再腐蚀，适合填补白色目标内部的小黑洞。

核越大，处理效果通常越明显，但过大的核也可能损伤小目标或改变边缘。

### `cv::findContours()`

- `RETR_EXTERNAL`：只提取最外层轮廓；
- `CHAIN_APPROX_SIMPLE`：压缩直线段上的冗余点。

`contourArea()` 负责计算轮廓面积，最小面积阈值只决定轮廓是否通过筛选，不会让外接矩形本身变大。

### `cv::waitKey()`

`waitKey(1)` 不只是等待按键，也会让 HighGUI 处理窗口刷新和键盘事件。检测到 `Esc` 的键值 `27` 时，程序退出循环。

## 源码编码说明

`main.cpp` 使用 UTF-8 中文注释。MSVC 对无 BOM 文件可能默认按系统代码页读取，因此 CMake 显式加入了 `/utf-8`：

```cmake
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
```

这可以避免中文注释被错误解析后产生看似无关的语法错误和“变量未声明”连锁报错。

## 当前验证状态

- 已在当前环境中完成 CMake 配置；
- 已使用 MSVC 和 OpenCV 4.12.0 成功编译；
- 本次整理未重新占用摄像头进行运行验证，因此不记录新的实际检测结果。

## 官方资料

- [OpenCV 4.12.0：`cv::VideoCapture`](https://docs.opencv.org/4.12.0/d8/dfe/classcv_1_1VideoCapture.html)
- [OpenCV 4.12.0：HSV 与 `inRange()`](https://docs.opencv.org/4.12.0/da/d97/tutorial_threshold_inRange.html)
- [OpenCV 4.12.0：形态学开、闭运算](https://docs.opencv.org/4.12.0/d3/dbe/tutorial_opening_closing_hats.html)
- [OpenCV 4.12.0：轮廓入门](https://docs.opencv.org/4.12.0/d4/d73/tutorial_py_contours_begin.html)
- [Microsoft Learn：MSVC `/utf-8` 编译选项](https://learn.microsoft.com/zh-cn/cpp/build/reference/utf-8-set-source-and-executable-character-sets-to-utf-8?view=msvc-170)
