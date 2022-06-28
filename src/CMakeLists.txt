cmake_minimum_required(VERSION 3.10)

option(JALI_BUILD_RELEASE "release build for end user" OFF)

set(JALI_HEADERS
    "jlpch.h"
    "Scanner.h"
    "ErrorHandler.h"
    "Literal.h"
)

set(JALI_SOURCES
    "Scanner.cpp"
    "ErrorHandler.cpp"
    "Literal.cpp"
)

source_group("Header Files" FILES ${JALI_HEADERS})
source_group("Source Files" FILES ${JALI_SOURCES})

add_library(jali_static STATIC ${JALI_HEADERS} ${JALI_SOURCES})

target_include_directories(jali_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_precompile_headers(jali_static PRIVATE "jlpch.h")