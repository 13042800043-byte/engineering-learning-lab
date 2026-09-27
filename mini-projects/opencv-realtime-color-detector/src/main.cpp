#include "opencv2/opencv.hpp"
#include <iostream>
#include <vector>
#include <string>

int main()
{
    // ==============================
    // 1. 打开摄像头
    // ==============================
    // 设备编号 0 通常表示系统默认摄像头；构造对象时会立即尝试打开它。
    cv::VideoCapture cap(0);

    if (!cap.isOpened())
    {
        std::cerr << "Cannot open camera!" << std::endl;
        return -1;
    }

    // 向摄像头后端请求 1280×720。驱动不支持时，实际分辨率可能与请求值不同。
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720);

    // ==============================
    // 2. HSV 蓝色阈值
    // ==============================
    // OpenCV 的 8 位 HSV 图像中，H 通常取 0～179。
    // 同时设置 S/V 下界，可以减少灰色区域和过暗区域被误判为蓝色。
    cv::Scalar lowerBlue(100, 80, 50);
    cv::Scalar upperBlue(130, 255, 255);

    // ==============================
    // 3. 形态学 Kernel
    // ==============================
    // Kernel 决定形态学操作观察多大的邻域；尺寸越大，处理作用越强，
    // 但也更可能抹掉较小的真实目标或改变目标边缘。
    cv::Mat kernel = cv::getStructuringElement(
        cv::MORPH_RECT,
        cv::Size(5, 5)
    );

    // 面积小于该值的轮廓不会被当作目标，可减少小噪点产生的误检框。
    double minArea = 5000.0;

    // FPS 计算
    int64 lastTime = cv::getTickCount();

    while (true)
    {
        // ==============================
        // 4. 获取摄像头一帧
        // ==============================
        cv::Mat frame;
        cap >> frame;

        if (frame.empty())
        {
            std::cerr << "Empty frame!" << std::endl;
            break;
        }

        // 在副本上绘制标注，避免改变本轮读取的原始 frame。
        cv::Mat resultImage = frame.clone();

        // ==============================
        // 5. BGR -> HSV
        // ==============================
        cv::Mat hsv;

        cv::cvtColor(
            frame,
            hsv,
            cv::COLOR_BGR2HSV
        );

        // ==============================
        // 6. HSV Threshold
        // ==============================
        cv::Mat mask;

        // 范围内像素在 mask 中变为白色，其余像素变为黑色。
        cv::inRange(
            hsv,
            lowerBlue,
            upperBlue,
            mask
        );

        // ==============================
        // 7. Morphology
        // ==============================
        cv::Mat cleanMask;

        // 开运算：先腐蚀、再膨胀，主要清除孤立的小白色噪点。
        cv::morphologyEx(
            mask,
            cleanMask,
            cv::MORPH_OPEN,
            kernel
        );

        // 闭运算：先膨胀、再腐蚀，主要填补目标内部的小黑色孔洞。
        cv::morphologyEx(
            cleanMask,
            cleanMask,
            cv::MORPH_CLOSE,
            kernel
        );

        // ==============================
        // 8. Find Contours
        // ==============================
        std::vector<std::vector<cv::Point>> contours;

        // RETR_EXTERNAL 只取最外层轮廓；CHAIN_APPROX_SIMPLE 会压缩直线段冗余点。
        cv::findContours(
            cleanMask,
            contours,
            cv::RETR_EXTERNAL,
            cv::CHAIN_APPROX_SIMPLE
        );

        int targetCount = 0;

        // ==============================
        // 9. Target Filtering
        // ==============================
        for (size_t i = 0; i < contours.size(); ++i)
        {
            double area = cv::contourArea(contours[i]);

            // 过滤小区域
            if (area < minArea)
            {
                continue;
            }

            ++targetCount;

            // ==============================
            // 10. Bounding Box
            // ==============================
            cv::Rect box =
                cv::boundingRect(contours[i]);

            // ==============================
            // 11. 中心点
            // ==============================
            int centerX =
                box.x + box.width / 2;

            int centerY =
                box.y + box.height / 2;

            // 这里计算的是外接矩形中心，不是基于图像矩的轮廓质心。
            cv::Point center(
                centerX,
                centerY
            );

            // ==============================
            // 12. 画 Bounding Box
            // ==============================
            cv::rectangle(
                resultImage,
                box,
                cv::Scalar(0, 255, 0),
                2
            );

            // 画中心点
            cv::circle(
                resultImage,
                center,
                5,
                cv::Scalar(0, 0, 255),
                -1
            );

            // ==============================
            // 13. 显示中心坐标
            // ==============================
            std::string centerText =
                "Center: (" +
                std::to_string(centerX) +
                ", " +
                std::to_string(centerY) +
                ")";

            cv::putText(
                resultImage,
                centerText,
                cv::Point(box.x, box.y - 10),
                cv::FONT_HERSHEY_SIMPLEX,
                0.6,
                cv::Scalar(0, 255, 0),
                2
            );

            // ==============================
            // 14. 显示面积
            // ==============================
            std::string areaText =
                "Area: " +
                std::to_string(static_cast<int>(area));

            cv::putText(
                resultImage,
                areaText,
                cv::Point(box.x, box.y + box.height + 25),
                cv::FONT_HERSHEY_SIMPLEX,
                0.6,
                cv::Scalar(0, 255, 0),
                2
            );
        }

        // ==============================
        // 15. FPS
        // ==============================
        int64 currentTime = cv::getTickCount();

        // 相邻两帧之间的 Tick 差换算为本轮近似 FPS。
        double fps =
            cv::getTickFrequency() /
            (currentTime - lastTime);

        lastTime = currentTime;

        std::string fpsText =
            "FPS: " +
            std::to_string(static_cast<int>(fps));

        cv::putText(
            resultImage,
            fpsText,
            cv::Point(20, 35),
            cv::FONT_HERSHEY_SIMPLEX,
            0.8,
            cv::Scalar(0, 255, 255),
            2
        );

        // 显示目标数量
        std::string countText =
            "Targets: " +
            std::to_string(targetCount);

        cv::putText(
            resultImage,
            countText,
            cv::Point(20, 70),
            cv::FONT_HERSHEY_SIMPLEX,
            0.8,
            cv::Scalar(0, 255, 255),
            2
        );

        // ==============================
        // 16. 显示结果
        // ==============================
        cv::imshow(
            "Color Target Detector",
            resultImage
        );

        cv::imshow(
            "Binary Mask",
            cleanMask
        );

        // waitKey() 不仅检测按键，也让 HighGUI 处理窗口刷新等事件。
        // 传入 1 表示至少等待约 1 ms；按 ESC（键值 27）退出循环。
        int key = cv::waitKey(1);

        if (key == 27)
        {
            break;
        }
    }

    // ==============================
    // 17. 释放资源
    // ==============================
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
