cmake_minimum_required(VERSION 3.26)
project(untitled18 C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled18 main.c
        libs/data_structures/matrix/matrix.h
        libs/data_structures/matrix/matrix.c
        tasks.c
        tasks_2.c
        task_3.c)

add_subdirectory(libs)
target_link_libraries(untitled18 data_structures)