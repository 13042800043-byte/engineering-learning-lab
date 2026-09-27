cmake_minimum_required(VERSION 3.21)

project(opencv-realtime-color-detector LANGUAGES CXX)

# main.cpp 使用 UTF-8 中文注释，避免 MSVC 按系统代码页误解析源码。
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

find_package(
    OpenCV CONFIG REQUIRED
    COMPONENTS
        core
        imgcodecs
        highgui
        imgproc
        videoio
)
add_executable(opencv-realtime-color-detector src/main.cpp)
target_compile_features(opencv-realtime-color-detector PRIVATE cxx_std_17)
target_link_libraries(opencv-realtime-color-detector PRIVATE ${OpenCV_LIBS})
