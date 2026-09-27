#include "mini_project/blue_object_detector.hpp"

#include <stdexcept>

#include <opencv2/imgproc.hpp>

namespace mini_project {

DetectionResult detectBlueObjects(
    const cv::Mat& bgr_image,
    const DetectionSettings& settings)
{
    if (bgr_image.empty()) {
        throw std::invalid_argument("The input image must not be empty.");
    }

    cv::Mat hsv_image;
    // HSV 将“颜色种类”集中在 H 通道，比直接比较 BGR 三通道更便于按颜色分割。
    cv::cvtColor(bgr_image, hsv_image, cv::COLOR_BGR2HSV);

    DetectionResult result;
    // 范围内像素置白，其余像素置黑，得到供形态学和轮廓检测使用的二值掩膜。
    cv::inRange(hsv_image, settings.lower_hsv, settings.upper_hsv, result.mask);

    // 开运算先腐蚀再膨胀，在提取轮廓前清理尺寸较小的白色噪点。
    const cv::Mat kernel = cv::getStructuringElement(
        cv::MORPH_RECT,
        settings.morphology_kernel_size);
    cv::morphologyEx(result.mask, result.mask, cv::MORPH_OPEN, kernel);

    std::vector<std::vector<cv::Point>> contours;
    // 这里只关心最外层边界；CHAIN_APPROX_SIMPLE 会省略直线段上的冗余点。
    cv::findContours(
        result.mask,
        contours,
        cv::RETR_EXTERNAL,
        cv::CHAIN_APPROX_SIMPLE);

    result.contour_count = contours.size();
    result.annotated_image = bgr_image.clone();

    for (std::size_t index = 0; index < contours.size(); ++index) {
        const auto& contour = contours[index];

        cv::drawContours(
            result.annotated_image,
            contours,
            static_cast<int>(index),
            cv::Scalar(0, 255, 0),
            2);

        // 小轮廓仍保留轮廓线，但不标记为目标，避免给噪声绘制检测框。
        if (cv::contourArea(contour) < settings.minimum_contour_area) {
            continue;
        }

        const cv::Rect box = cv::boundingRect(contour);
        result.bounding_boxes.push_back(box);
        cv::rectangle(result.annotated_image, box, cv::Scalar(0, 255, 0), 2);

        const cv::Point center(
            box.x + box.width / 2,
            box.y + box.height / 2);
        cv::circle(result.annotated_image, center, 5, cv::Scalar(0, 0, 255), cv::FILLED);
    }

    return result;
}

}  // namespace mini_project
