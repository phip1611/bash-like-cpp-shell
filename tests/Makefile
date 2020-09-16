# Copyright 2020 - Philipp Schuster.
#
# This file/project is licensed under a MIT license.
# You can find the LICENSE file in the repository.

OBJ_DIR = build

CPPFLAGS  = -ggdb -Wall -Werror -Wshadow -Weffc++ -pedantic -std=c++17
INCFLAGS  = -I../src

# list all test binaries here
all: $(OBJ_DIR)/strings_test

# strings_test
$(OBJ_DIR)/strings_test: strings_test.cpp ../src/strings.cpp | $(OBJ_DIR)
	g++ $(INCFLAGS) $(CPPFLAGS) -o $@ $+


# if OBJ_DIR doesn't exist: create
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

.PHONY: clean

clean:
	rm -rf $(OBJ_DIR)

