cmake_minimum_required(VERSION 3.1)

# 1.Set project name
project(Sample VERSION 1.0)

# 2.Set c++ version
set(CMAKE_CXX_STANDARD 11)
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

# 5、executable
add_executable(Sample "")

# 6、add sources
file(GLOB_RECURSE srcs
	${CMAKE_CURRENT_LIST_DIR}/Sample/*.h
	${CMAKE_CURRENT_LIST_DIR}/Sample/*.hpp
 	${CMAKE_CURRENT_LIST_DIR}/Sample/*.cpp
)

target_sources(Sample
PRIVATE
 	${srcs}
)

source_group(TREE ${CMAKE_CURRENT_LIST_DIR}/Sample FILES ${srcs})

# 7、Link
target_link_libraries(Sample
PRIVATE
	Magic
)

# 8、add include directories
target_include_directories(Sample
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Magic/src
)

# 9、Startup Project
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT Sample)