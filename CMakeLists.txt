cmake_minimum_required(VERSION 3.19)
project(assign1 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(assign1
        mem_1.c
        mem_2.c
        mem_3.c
        memlayout.c
        memlayout.h)
