cmake_minimum_required(VERSION 3.1)

# https://blog.csdn.net/beibeix2015/article/details/117084939
# https://discourse.cmake.org/t/generating-c-net6-projects-problems-with-dotnet-sdk/5745
# https://stackoverflow.com/questions/66823316/set-a-target-vs-global-property-that-applies-to-all-targets-using-cmake

# 1.set project name
project(MagicCLR LANGUAGES CSharp)

# 可执行文件输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../Resources/Scripts)

# 2、add executable
file(GLOB_RECURSE srcs
    ${CMAKE_CURRENT_LIST_DIR}/Src/*.cs
)

add_executable(MagicCLR
    ${srcs}
)

# 3.compile options
set_target_properties(MagicCLR PROPERTIES
    DOTNET_SDK "Microsoft.NET.Sdk"
    DOTNET_TARGET_FRAMEWORK "net5.0"
)

set_target_properties(MagicCLR PROPERTIES 
	VS_GLOBAL_AllowUnsafeBlocks true
)
