cmake_minimum_required(VERSION 3.22)
project(omni-table)

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
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "AMD64")
        set(ARCH_WIN64 TRUE)
        message(STATUS "Building for Windows 64-bit")
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "x86")
        set(ARCH_WIN86 TRUE)
        message(STATUS "Building for Windows x86")
    endif()
endif()



set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# CMake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_sanitizers INTERFACE)

include(AddGTest)
include(AddBenchmark)
include(CompilerWarnings)
include(Sanitizers)

if (NOT MSVC)
	include(AddBenchmark)
endif()

find_package(Threads REQUIRED)

set_project_warnings(project_warnings)
enable_sanitizers(project_sanitizers)

enable_testing()

if (NOT MSVC)
	add_subdirectory(benchmark_test)
endif()

add_subdirectory(tests)
add_subdirectory(examples)

# testing
add_subdirectory(external/gtest)

add_library(omni-table STATIC )

target_sources(omni-table PRIVATE 
    src/table.cpp
    src/cell.cpp
    src/row.cpp
	src/formatter.cpp
    )

target_link_libraries(omni-table PRIVATE project_warnings)

if (ENABLE_SANITIZER_ADDRESS)
    target_link_libraries(omni-table PRIVATE project_sanitizers)
endif()
