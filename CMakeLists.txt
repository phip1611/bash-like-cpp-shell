cmake_minimum_required(VERSION 3.10)
project(phipsshell)

set(CMAKE_CXX_STANDARD 17)

set(LINK_LIBRARIES    "readline")

set(CMAKE_CXX_FLAGS     "-Wall -Werror -Wshadow -Weffc++ -pedantic ")

# main executable
add_executable(phipsshell
        src/main.cpp
        src/strings.cpp
        src/properties.cpp
        src/parse.cpp
        src/action.cpp
        src/alias.cpp
)
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

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_include_directories(phipsshell PRIVATE
            include
    )
    target_link_directories(phipsshell PRIVATE
            /usr/local/opt/readline/lib/
    )
endif()