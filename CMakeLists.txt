cmake_minimum_required(VERSION 3.10)
project(phipsshell)

set(CMAKE_CXX_STANDARD 17)

set(LINK_LIBRARIES    "readline")

set(CMAKE_CXX_FLAGS     "-Wall -Werror -Wshadow -Weffc++ -pedantic ")

add_executable(phipsshell
        src/main.cpp
        src/lib.cpp
)

#add_executable(test
#        pipe-close-test/test.c
#)

# from "readline" cmakes generates "-lreadline" etc
target_link_libraries(phipsshell ${LINK_LIBRARIES})