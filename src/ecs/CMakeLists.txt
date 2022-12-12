cmake_minimum_required(VERSION 3.22)

set(CMAKE_C_STANDARD 23)

add_library(ecs ecs.c containers.c queue.c sort.c)

