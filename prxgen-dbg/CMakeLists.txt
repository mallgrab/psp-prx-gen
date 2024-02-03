cmake_minimum_required(VERSION 3.21)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")
project(prxgen C)

set(CMAKE_C_STANDARD 17)

add_executable(prxgen psp-prxgen.c)
