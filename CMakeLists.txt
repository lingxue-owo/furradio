cmake_minimum_required(VERSION 3.0)

project(furradio LANGUAGES C)

add_executable(furradio main.c)

install(TARGETS furradio RUNTIME DESTINATION bin)
