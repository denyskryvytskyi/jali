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

if(CMAKE_GENERATOR MATCHES "Visual Studio")
    set_property(
        DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        PROPERTY
        VS_STARTUP_PROJECT jali
    )
endif()

add_subdirectory(src)
add_subdirectory(test)

# jali runtime
set(JALI_RUNTIME_SOURCE
    "src/main.cpp"
)

add_executable(jali ${JALI_RUNTIME_SOURCE})

target_link_libraries(jali PUBLIC jali_static)

target_precompile_headers(jali PRIVATE "src/jlpch.h")

set_target_properties(jali PROPERTIES 
                      VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Debug)