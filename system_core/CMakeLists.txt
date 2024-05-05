cmake_minimum_required(VERSION 3.17)

project(Study-Operating-System)

set(CMAKE_CXX_STANDARD 20)

## Include directories for headers
include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/include/device
        ${PROJECT_SOURCE_DIR}/include/io
        ${PROJECT_SOURCE_DIR}/include/lib
)

# Adds source files to executable
add_executable(
        Study-Operating-System
        src/main.cc
        src/lib/tools.c
        src/lib/finit.cc
        src/initfini.c
        src/device/CgaChannel.cc
        src/device/CgaScreen.cc
        src/io/PrintStream.cc
)

set_target_properties(Study-Operating-System PROPERTIES
        COMPILE_OPTIONS "-fno-exceptions;-fno-rtti"
)