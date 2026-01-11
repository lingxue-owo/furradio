cmake_minimum_required(VERSION 3.10)

project(furradio LANGUAGES C)

include_directories(include/)
include_directories(inc/)
add_subdirectory(src/)
add_subdirectory(tests/)
add_subdirectory(apps/)

# install(TARGETS furradio RUNTIME DESTINATION bin)
