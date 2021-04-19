cmake_minimum_required(VERSION 2.8.12.2)
project(ps_parprog_2021 C)

execute_process(COMMAND module load gcc/8.2.0)
set(CMAKE_C_FLAGS "-std=gnu11 -O3")
set(SOURCES1 ./task1/example.c)
set(SOURCES2 ./task2/flush.c)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
endif()

add_executable(task1 ${SOURCES1})
add_executable(task2 ${SOURCES2})