#include "mini_project/blue_object_detector.hpp"

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>

#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

namespace {

void printUsage(const char* executable_name)
{
    std::cout << "Usage: " << executable_name
              << " <input-image> [output-directory] [--no-gui]\n";
}
bool saveImage(const std::filesystem::path& path, const cv::Mat& image)
{
    if (cv::imwrite(path.string(), image)) {
        return true;
    }

    std::cerr << "Failed to write image: " << path << '\n';
    return false;
}

}  // namespace

int main(int argc, char* argv[])
{
    if (argc < 2 || argc > 4) {
        printUsage(argv[0]);
        return EXIT_FAILURE;
    }

    const std::filesystem::path input_path = argv[1];
    std::filesystem::path output_directory = "output";
    bool output_directory_set = false;
    bool show_windows = true;

    for (int index = 2; index < argc; ++index) {
        const std::string argument = argv[index];
        if (argument == "--no-gui") {
            show_windows = false;
        } else if (!output_directory_set) {
            output_directory = argument;
            output_directory_set = true;
        } else {
            printUsage(argv[0]);
            return EXIT_FAILURE;
        }
    }

    const cv::Mat color_image = cv::imread(input_path.string(), cv::IMREAD_COLOR);
    // imread() 读取失败时返回空 Mat；必须先检查，避免后续算法收到无效输入。
    if (color_image.empty()) {
        std::cerr << "Could not read input image: " << input_path << '\n';
        return EXIT_FAILURE;
    }

    cv::Mat grayscale_image;
    cv::cvtColor(color_image, grayscale_image, cv::COLOR_BGR2GRAY);

    const mini_project::DetectionResult result =
        mini_project::detectBlueObjects(color_image);

    std::error_code directory_error;
    std::filesystem::create_directories(output_directory, directory_error);
    if (directory_error) {
        std::cerr << "Could not create output directory: "
                  << output_directory << " (" << directory_error.message() << ")\n";
        return EXIT_FAILURE;
    }

    const bool output_saved =
        saveImage(output_directory / "grayscale.png", grayscale_image)
        && saveImage(output_directory / "blue_mask.png", result.mask)
        && saveImage(output_directory / "annotated.png", result.annotated_image);
    if (!output_saved) {
        return EXIT_FAILURE;
    }

    std::cout << "OpenCV version: " << CV_VERSION << '\n'
              << "Contours found: " << result.contour_count << '\n'
              << "Contours above area threshold: " << result.bounding_boxes.size() << '\n'
              << "Results saved to: " << std::filesystem::absolute(output_directory) << '\n';

    if (show_windows) {
        cv::imshow("Original", color_image);
        cv::imshow("Blue mask", result.mask);
        cv::imshow("Detected contours", result.annotated_image);
        // waitKey() 同时等待按键并处理 HighGUI 窗口事件，否则窗口可能无法正常刷新。
        cv::waitKey(0);
    }

    return EXIT_SUCCESS;
}
