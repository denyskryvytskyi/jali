cmake_minimum_required(VERSION 3.10)

set(JALI_TEST_SOURCES
    "doctest.h"
    "DoctestMain.cpp"
    "ScannerTest.cpp"
)

source_group("src" FILES ${JALI_TEST_SOURCES})

add_executable(jali_test  ${JALI_TEST_SOURCES})

target_link_libraries(jali_test PUBLIC jali_static)

set_target_properties(jali_test PROPERTIES 
                      VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Debug)

target_precompile_headers(jali_test PRIVATE ${CMAKE_SOURCE_DIR}/src/jlpch.h)