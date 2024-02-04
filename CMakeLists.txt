cmake_minimum_required(VERSION 3.00)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")
project(prxgen C)

set(CMAKE_C_STANDARD 99)

add_executable(prxgen psp-prxgen.c)