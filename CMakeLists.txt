cmake_minimum_required(VERSION 3.1)

# 1.Set project name
project(SampleSolution VERSION 1.0)

# 2.Set c++ version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 3.Outputs
# 静态库输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib)
# 动态库输出目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
# 可执行文件输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)

# 4.Add subdirectory
add_subdirectory(Magic)
add_subdirectory(Sample)

# 5、Startup Project
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT Sample)