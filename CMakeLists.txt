cmake_minimum_required(VERSION 3.0)

project(furradio LANGUAGES C)

include_directories(include/)
add_subdirectory(src/)
add_subdirectory(tests/)

# install(TARGETS furradio RUNTIME DESTINATION bin)
