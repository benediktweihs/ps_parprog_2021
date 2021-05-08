cmake_minimum_required(VERSION 2.8.12.2)
project(ps_parprog_2021 C)
execute_process(COMMAND module load gcc/10.3.0)

#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS "-std=gnu11 -O1")
set(SOURCES1 ./task1/task1.c)
find_package(OpenMP)

if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
endif()

add_executable(task1 ${SOURCES1})
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ftree-vectorize")
add_executable(task1_parallel ${SOURCES1})
