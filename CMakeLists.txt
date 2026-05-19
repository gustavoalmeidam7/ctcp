cmake_minimum_required(VERSION 3.16)
project(HTTPC LANGUAGES C)

if(DEBUG)
    SET(CMAKE_C_FLAGS_DEBUG "-g -O0 -Wall")
    set(CMAKE_EXPORT_COMPILE_COMMANDS on)
    set(CMAKE_BUILD_TYPE Debug)
    message("DEBUG MODE ON")
endif()

file(GLOB_RECURSE _src
    ${PROJECT_SOURCE_DIR}/src/*.c
)

add_executable(HTTPC ${_src})

target_include_directories(HTTPC PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)
