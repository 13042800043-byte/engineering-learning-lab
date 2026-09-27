#pragma once

#include <cstddef>
#include <vector>

#include <opencv2/core.hpp>

namespace mini_project {

struct DetectionSettings {
    cv::Scalar lower_hsv{90, 80, 50};
    cv::Scalar upper_hsv{140, 255, 255};
    cv::Size morphology_kernel_size{5, 5};
    double minimum_contour_area{5000.0};
};

struct DetectionResult {
    cv::Mat mask;
    cv::Mat annotated_image;
    std::vector<cv::Rect> bounding_boxes;
    std::size_t contour_count{};
};

DetectionResult detectBlueObjects(
    const cv::Mat& bgr_image,
    const DetectionSettings& settings = {});

}  // namespace mini_project
