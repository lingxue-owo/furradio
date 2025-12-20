cmake_minimum_required(VERSION 3.0)

project(furradio LANGUAGES C)

add_executable(bmp_tb bmp_tb.c)
target_link_libraries(bmp_tb bmp_library)
