cmake_minimum_required(VERSION 3.10)

project(furradio LANGUAGES C)

add_executable(sstv_testcard sstv_testcard/sstv_testcard.c)
target_link_libraries(sstv_testcard bmp_library)
target_link_libraries(sstv_testcard sstv_library)
#target_link_libraries(sstv_testcard m)

