cmake_minimum_required(VERSION 3.20)

project(freertos_task_basics_lab LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

include(FetchContent)

add_library(freertos_config INTERFACE)
target_include_directories(freertos_config SYSTEM
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_compile_definitions(freertos_config
    INTERFACE
        projCOVERAGE_TEST=0
        WIN32_LEAN_AND_MEAN
)
set(FREERTOS_PORT MSVC_MINGW CACHE STRING "FreeRTOS Windows simulator port" FORCE)
set(FREERTOS_HEAP 4 CACHE STRING "FreeRTOS heap implementation" FORCE)

set(FREERTOS_GIT_CONFIG)
if(DEFINED ENV{HTTPS_PROXY} AND NOT "$ENV{HTTPS_PROXY}" STREQUAL "")
    set(FREERTOS_GIT_CONFIG GIT_CONFIG "http.proxy=$ENV{HTTPS_PROXY}")
endif()

FetchContent_Declare(
    freertos_kernel
    GIT_REPOSITORY https://github.com/FreeRTOS/FreeRTOS-Kernel.git
    GIT_TAG V11.3.1
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    ${FREERTOS_GIT_CONFIG}
)
FetchContent_MakeAvailable(freertos_kernel)

add_executable(freertos_task_lab src/main.c)
target_link_libraries(freertos_task_lab PRIVATE freertos_kernel)

if(MINGW)
    target_compile_options(freertos_task_lab PRIVATE -Wall -Wextra -Wpedantic)
endif()

enable_testing()
find_program(POWERSHELL_EXECUTABLE NAMES pwsh powershell REQUIRED)
add_test(
    NAME freertos_task_output
    COMMAND
        ${POWERSHELL_EXECUTABLE}
        -NoProfile
        -ExecutionPolicy Bypass
        -File ${CMAKE_CURRENT_SOURCE_DIR}/tests/verify_output.ps1
        -Executable $<TARGET_FILE:freertos_task_lab>
)
