cmake_minimum_required(VERSION 3.20)

cmake_policy(SET CMP0123 NEW)

project(lengthOfLongestSubstring C)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(pro_include
    ${CMAKE_CURRENT_SOURCE_DIR}/../utils/
)
include_directories(${utils_inc})

file(GLOB_RECURSE pro_source
    ${CMAKE_CURRENT_SOURCE_DIR}/../utils/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lengthOfLongestSubstring.c
)

add_executable(${PROJECT_NAME} ${pro_source})
