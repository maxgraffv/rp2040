cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_PATH "/opt/pico-sdk")

include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(RP2040_simplified C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

pico_sdk_init()

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

add_library(i2c_lib src/i2c.c)

target_link_libraries(i2c_lib pico_stdlib hardware_i2c)

add_executable( main example/main.c)

target_link_libraries( main i2c_lib)

pico_add_extra_outputs(main)

pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 0)
