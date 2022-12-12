project(all_tests C) 

add_executable(ecs_tests ecs_tests.c)
target_link_libraries(ecs_tests PRIVATE ecs raylib)

add_test(ecs_tests ecs_tests)

