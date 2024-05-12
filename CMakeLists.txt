cmake_minimum_required(VERSION 3.22)
project(cc-table)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86")
        set(ARCH_LNX86 TRUE)
        message(STATUS "Building for Linux x86")
    endif()
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
        set(ARCH_MCA64 TRUE)
        message(STATUS "Building for macOS 64-bit")
    endif()
endif()


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# CMake modules
# list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(Threads REQUIRED)

add_executable(cc-table src/main.cpp src/table.cpp)
