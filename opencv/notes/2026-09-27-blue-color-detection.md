# OpenCV 蓝色区域提取与轮廓标注

> 实践日期：2026-09-27
>
> 项目：[`mini-projects/opencv-color-detector`](../../mini-projects/opencv-color-detector/)
>
> 记录状态：已根据实际运行、源码和学习检测整理

## 本次实际完成

- 亲手编写并实际运行了一份静态图片颜色检测代码。
- 看到了颜色处理后的图片，以及被绿色方框标出的蓝色物体。
- 初始代码将读图、颜色转换、形态学处理、轮廓检测和窗口显示全部写在 `main.cpp` 中。
- 本次整理后，项目把图像处理逻辑与文件读写、窗口显示分开，并加入了不依赖个人图片的合成图测试。

本次记录只确认静态图片处理，没有把它写成实时摄像头颜色检测。

## 图像处理流程

```text
读取 BGR 图片
      ↓
BGR 转 HSV
      ↓
inRange() 生成蓝色二值掩膜
      ↓
MORPH_OPEN 清理小噪声
      ↓
findContours() 提取外轮廓
      ↓
contourArea() 按面积筛选
      ↓
boundingRect() 绘制外接矩形
      ↓
计算矩形中心并绘制中心点
```

程序还会把原图转换为灰度图，并分别保存灰度图、蓝色掩膜和最终标注图。

## 本次接触的核心接口

### 1. `cv::imread()` 与 `cv::imwrite()`

```cpp
const cv::Mat color_image = cv::imread(path, cv::IMREAD_COLOR);
cv::imwrite(output_path, image);
```

- `imread()` 从文件读取图片，并用 `cv::Mat` 保存像素数据；
- 读取失败时会返回空矩阵，因此应使用 `empty()` 检查；
- `imwrite()` 根据文件扩展名选择编码格式，并返回是否写入成功。

初始代码把图片路径写死在源码中。整理后的程序改为从命令行接收图片路径，这样换图片时不需要修改并重新编译源码。

### 2. `cv::cvtColor()`

```cpp
cv::cvtColor(color_image, hsv_image, cv::COLOR_BGR2HSV);
```

OpenCV 默认以 BGR 通道顺序读取彩色图片。转换到 HSV 后：

- H 表示色相，可用于区分颜色种类；
- S 表示饱和度；
- V 表示明度。

本次学习检测中，已经知道 HSV 更适合过滤其他颜色，但还不能完整说明后续步骤。需要补充的是：HSV 只是把颜色换成更便于设定范围的表示方式，真正完成范围判断的是 `inRange()`。

### 3. `cv::inRange()`

```cpp
cv::inRange(
    hsv_image,
    cv::Scalar(90, 80, 50),
    cv::Scalar(140, 255, 255),
    mask);
```

它检查每个像素的 H、S、V 是否都落在给定上下界内：

- 满足条件的像素在掩膜中变为白色；
- 不满足条件的像素变为黑色。

因此，当前参数得到的是一张“蓝色区域为白，其余区域为黑”的二值图。阈值与光照、图片内容有关，不能当成对所有蓝色目标都通用的固定值。

### 4. `cv::morphologyEx()` 与 `MORPH_OPEN`

```cpp
const cv::Mat kernel = cv::getStructuringElement(
    cv::MORPH_RECT,
    cv::Size(5, 5));
cv::morphologyEx(mask, mask, cv::MORPH_OPEN, kernel);
```

开运算由“先腐蚀、再膨胀”组成。在当前流程中，它用于减少二值掩膜中尺寸较小的白色噪点。

本次学习检测时还不能说明 `MORPH_OPEN` 的作用，因此该部分属于复盘补充，尚需通过修改核尺寸并观察结果来巩固。核变大时通常能清除更大的噪点，但也更可能损伤真正的蓝色区域。

### 5. `cv::findContours()`

```cpp
cv::findContours(
    mask,
    contours,
    cv::RETR_EXTERNAL,
    cv::CHAIN_APPROX_SIMPLE);
```

- `RETR_EXTERNAL`：只提取最外层轮廓；
- `CHAIN_APPROX_SIMPLE`：压缩直线段上重复的轮廓点，减少需要保存的数据。

轮廓可以理解为二值图中连续白色区域的边界。当前代码先找到轮廓，再计算其面积和外接矩形。

### 6. `cv::contourArea()` 与面积阈值

```cpp
if (cv::contourArea(contour) < minimum_contour_area) {
    continue;
}
```

`contourArea()` 计算轮廓面积。`minimum_contour_area` 是是否把轮廓当成目标并画框的门槛。

学习检测时最初预测：把 `minArea` 调大后变化可能不大，或者框会超出一些。这个判断需要修正：

- 调大阈值不会直接改变某个轮廓的边界，也不会让它的外接矩形变大；
- 它只会让面积较小的轮廓不能通过筛选；
- 阈值继续增大时，检测框数量可能减少到零；
- 仍能通过筛选的轮廓，其外接矩形基本保持原样。

### 7. `cv::boundingRect()`、`cv::rectangle()` 与 `cv::circle()`

```cpp
const cv::Rect box = cv::boundingRect(contour);
cv::rectangle(image, box, cv::Scalar(0, 255, 0), 2);

const cv::Point center(
    box.x + box.width / 2,
    box.y + box.height / 2);
cv::circle(image, center, 5, cv::Scalar(0, 0, 255), cv::FILLED);
```

- `boundingRect()` 计算与图像坐标轴平行的外接矩形；
- `rectangle()` 绘制绿色检测框；
- 矩形中心由左上角坐标、宽和高计算；
- `circle()` 在中心位置绘制红色实心圆。

## 项目结构整理

初始实现集中在一个 `main.cpp` 中。为了方便以后复习，整理后分为三层：

```text
main.cpp
  └─ 参数、文件读写、结果保存和窗口显示

blue_object_detector.cpp
  └─ HSV 分割、开运算、轮廓和目标标注

blue_object_detector_test.cpp
  └─ 使用合成蓝色图形验证面积过滤和错误输入处理
```

核心处理函数返回：

- 清理后的二值掩膜；
- 绘制轮廓与目标框后的图片；
- 通过面积筛选的外接矩形；
- 找到的原始外轮廓数量。

## 本次验证结果

以下结果由代理在当前环境中实际验证，不写成用户独立完成的测试结论：

- 使用 MSVC、CMake、vcpkg 和 OpenCV 4.12.0 成功构建；
- CTest 合成图测试通过；
- 使用本次练习图片进行无窗口运行，成功生成三张结果图；
- 实际找到 2 个蓝色外轮廓，2 个轮廓都通过了默认面积阈值；
- 标注结果中两个蓝色数字分别获得绿色外接矩形和红色中心点。

## 当前理解与薄弱点

已经确认：

- HSV 比直接使用 BGR 更便于按颜色范围进行筛选；
- 实际运行后能观察到蓝色物体被绿色框标出。

还需要复习和实操：

- `inRange()` 如何利用 HSV 上下界生成二值掩膜；
- 开运算为什么能清理小白点，以及核尺寸变化的影响；
- 面积阈值只决定轮廓能否通过筛选，不负责扩大外接矩形。

## 建议的下一次实操

1. 分别把最小轮廓面积改为 `1000`、`10000` 和一个大于所有目标面积的值，记录检测框数量。
2. 分别使用 `3 × 3`、`5 × 5`、`9 × 9` 的形态学核，对比掩膜边缘和小噪点。
3. 调整 HSV 的 H 下界或上界，观察蓝色区域何时开始缺失。
4. 在确认静态图片流程后，再把输入替换为摄像头逐帧图像，避免一次同时引入太多新变量。

## 官方参考资料

- [OpenCV 4.12.0：图像文件读写](https://docs.opencv.org/4.12.0/d4/da8/group__imgcodecs.html)
- [OpenCV 4.x：使用 HSV 和 `inRange()` 进行阈值分割](https://docs.opencv.org/4.x/da/d97/tutorial_threshold_inRange.html)
- [OpenCV 4.12.0：形态学开运算等变换](https://docs.opencv.org/4.12.0/d3/dbe/tutorial_opening_closing_hats.html)
- [OpenCV 4.12.0：轮廓入门](https://docs.opencv.org/4.12.0/d4/d73/tutorial_py_contours_begin.html)
- [OpenCV 4.x：轮廓外接矩形与圆](https://docs.opencv.org/4.x/da/d0c/tutorial_bounding_rects_circles.html)
