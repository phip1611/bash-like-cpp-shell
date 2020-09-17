# Copyright 2020 - Philipp Schuster.
#
# This file/project is licensed under a MIT license.
# You can find the LICENSE file in the repository.

cmake_minimum_required(VERSION 3.10)
project(phipsshell)

set(CMAKE_CXX_STANDARD 17)

set(LINK_LIBRARIES    "readline")

set(CMAKE_CXX_FLAGS   "-Wall -Werror -Wshadow -Weffc++ -pedantic ")

# main executable
file(GLOB phipsshell_SRC
        "src/*.hpp"
        "src/*.cpp"
)
add_executable(phipsshell ${phipsshell_SRC})

target_include_directories(phipsshell PRIVATE
        /usr/local/opt/readline/lib/
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

# Mac OS specific build
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_include_directories(phipsshell PRIVATE
            include
    )
    target_link_directories(phipsshell PRIVATE
            /usr/local/opt/readline/lib/
    )
endif()