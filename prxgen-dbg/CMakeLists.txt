cmake_minimum_required(VERSION 3.21)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -gdwarf-3")
project(prxgen C)

set(CMAKE_C_STANDARD 17)

add_executable(prxgen psp-prxgen.c)
add_custom_command(TARGET prxgen
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:prxgen> "/home/user/Projects/psp-prx-dbg/cube/")
