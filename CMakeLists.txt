cmake_minimum_required(VERSION 3.10)

project(jali
        VERSION 1.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CONFIGURATION_TYPES Debug Release)

option(JALI_BUILD_RELEASE "release build for end user" OFF)

if(JALI_BUILD_RELEASE)
    set(CMAKE_BUILD_TYPE "Release")
    add_compile_definitions(JALI_RELEASE)
else()
    set(CMAKE_BUILD_TYPE "Debug")
    add_compile_definitions(JALI_DEBUG)
endif()

add_subdirectory(src)