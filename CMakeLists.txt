cmake_minimum_required(VERSION 3.15)
project(Leaf LANGUAGES C ASM_NASM)

if(NOT DEFINED TARGET_ARCH)
    message(FATAL_ERROR "Please run ./configure to configure Leaf.")
endif()

set(KERNEL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/kernel")

if(NOT EXISTS "${KERNEL_DIR}")
    message(FATAL_ERROR "Directory '${KERNEL_DIR}' not found!")
endif()

add_subdirectory(${KERNEL_DIR})