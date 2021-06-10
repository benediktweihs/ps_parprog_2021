cmake_minimum_required(VERSION 2.8.12.2)
project(ps_parprog_2021 C)

execute_process(COMMAND module load gcc/8.2.0)
set(CMAKE_C_FLAGS "-std=gnu11 -O3")
set(SOURCES1_par task1/dellanoy.c)
set(SOURCES1_seq ./task1/dellanoy_sequential.c)
set(SOURCES2 ./task2/heat_stencil_2D.c)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
endif()

add_executable(task1_par ${SOURCES1_par})
add_executable(task1_seq ${SOURCES1_seq})
add_executable(task2 ${SOURCES2})
