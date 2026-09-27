cmake_minimum_required(VERSION 3.21)

project(mini-project LANGUAGES CXX)

# 源文件使用 UTF-8 中文注释；MSVC 无 BOM 时默认按系统代码页读取。
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

find_package(
    OpenCV CONFIG REQUIRED
    COMPONENTS
        core
        imgcodecs
        highgui
        imgproc
)
add_library(blue-object-detector src/blue_object_detector.cpp)
target_compile_features(blue-object-detector PUBLIC cxx_std_17)
target_include_directories(blue-object-detector PUBLIC include)
target_link_libraries(blue-object-detector PUBLIC ${OpenCV_LIBS})

add_executable(mini-project src/main.cpp)
target_compile_features(mini-project PRIVATE cxx_std_17)
target_link_libraries(mini-project PRIVATE blue-object-detector)

include(CTest)
if(BUILD_TESTING)
    add_executable(blue-object-detector-test tests/blue_object_detector_test.cpp)
    target_compile_features(blue-object-detector-test PRIVATE cxx_std_17)
    target_link_libraries(blue-object-detector-test PRIVATE blue-object-detector)
    add_test(NAME blue-object-detector-test COMMAND blue-object-detector-test)
endif()
