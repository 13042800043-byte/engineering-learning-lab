#include "mini_project/blue_object_detector.hpp"

#include <iostream>
#include <stdexcept>

#include <opencv2/imgproc.hpp>

int main()
{
    cv::Mat image = cv::Mat::zeros(180, 180, CV_8UC3);
    cv::rectangle(image, cv::Rect(20, 20, 100, 100), cv::Scalar(255, 0, 0), cv::FILLED);
    cv::rectangle(image, cv::Rect(150, 150, 5, 5), cv::Scalar(255, 0, 0), cv::FILLED);

    const mini_project::DetectionResult result = mini_project::detectBlueObjects(image);

    if (result.contour_count != 2) {
        std::cerr << "Expected two raw contours, got " << result.contour_count << '\n';
        return 1;
    }

    if (result.bounding_boxes.size() != 1) {
        std::cerr << "Expected one contour above the area threshold, got "
                  << result.bounding_boxes.size() << '\n';
        return 1;
    }

    const cv::Rect expected_box(20, 20, 100, 100);
    if (result.bounding_boxes.front() != expected_box) {
        std::cerr << "Unexpected bounding box: " << result.bounding_boxes.front() << '\n';
        return 1;
    }

    try {
        mini_project::detectBlueObjects(cv::Mat{});
        std::cerr << "Expected an empty input image to be rejected\n";
        return 1;
    } catch (const std::invalid_argument&) {
        // 空图像属于调用错误，不能被误认为“成功运行但没有检测结果”。
    }

    return 0;
}
