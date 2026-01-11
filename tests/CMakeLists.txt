cmake_minimum_required(VERSION 3.10)

project(furradio LANGUAGES C)

add_executable(bmp_tb bmp_tb.c)
target_link_libraries(bmp_tb bmp_library)

add_executable(wav_tb wav_tb.c)
target_link_libraries(wav_tb wav_library)

add_executable(ft8_tb ft8_tb.c)
target_link_libraries(ft8_tb ft8_library)
target_link_libraries(ft8_tb wav_library)
target_link_libraries(ft8_tb m)

