cmake_minimum_required(VERSION 2.8.12.2)
project(ps_parprog_2021 C)

execute_process(COMMAND module load gcc/8.2.0)
#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS "-std=gnu11 -O3")
set(SOURCES1 ./task1/task1.c)
set(SOURCES1_PARALLEL ./task1/task1_parallel.c)
find_package(OpenMP)

if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
endif()

add_executable(task1 ${SOURCES1})
add_executable(task1_par ${SOURCES1_PARALLEL})
