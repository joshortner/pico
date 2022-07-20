# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(FREERTOS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../lib/freertos)
set(ENV{PICO_SDK_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../../lib/pico-sdk)

# Include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Set name of project (as PROJECT_NAME) and C/C++ standards
project(freertos_demo C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# NOOOOOTTTTEEE: THIS SHOULD COME AFTER COMPILER DETECTION (THREE LINES ABOVE), OTHERWISE BAD THINGS HAPPEN
add_subdirectory(${FREERTOS_DIR} ${FREERTOS_DIR}/build/lib)

# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()

# Tell CMake where to find the executable source file
add_executable(
    ${PROJECT_NAME} 
    ${SRC_DIR}/main.c
)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(${PROJECT_NAME})

# Link to pico_stdlib (gpio, time, etc. functions)
target_link_libraries(
    ${PROJECT_NAME} 
    pico_stdlib
    freertos
)

# Enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)