cmake_minimum_required(VERSION 3.10)
project(phipsshell)

set(CMAKE_CXX_STANDARD 17)

set(LINK_LIBRARIES    "readline")

set(CMAKE_CXX_FLAGS     "-Wall -Werror -Wshadow -Weffc++ -pedantic ")

# main executable
add_executable(phipsshell
        src/main.cpp
        src/strings.cpp
)

# executable for strings test
add_executable(strings_test
        src/strings.cpp
        tests/strings_test.cpp
)
target_include_directories(strings_test PRIVATE
        src
)

# from "readline" cmakes generates "-lreadline" etc
target_link_libraries(phipsshell ${LINK_LIBRARIES})