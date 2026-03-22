cmake_minimum_required(VERSION 3.16)

if(DEBUG)
    SET(CMAKE_C_FLAGS_DEBUG "-g -O0 -Wall")
    set(CMAKE_BUILD_TYPE Debug)
    message("DEBUG MODE ON")
endif()

project(CTCP LANGUAGES C)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

file(GLOB_RECURSE _src
    ${PROJECT_SOURCE_DIR}/src/*.c
)

add_executable(CTCP ${_src})

target_include_directories(CTCP PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)
