cmake_minimum_required(VERSION 3.10)

project(jali
        VERSION 1.0
        LANGUAGES CXX)

set(JALI_HEADERS
    "Test.h"
)

set(JALI_SOURCES
    "main.cpp"
)

source_group("Header Files" FILES ${JALI_HEADERS})
source_group("Source Files" FILES ${JALI_SOURCES})

add_executable(jali ${JALI_HEADERS} ${JALI_SOURCES})