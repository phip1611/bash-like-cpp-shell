# Copyright 2020 - Philipp Schuster.
#
# This file/project is licensed under a MIT license.
# You can find the LICENSE file in the repository.

CC=g++

SRC_DIR = src
OBJ_DIR = build

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEP = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.d)

CPPFLAGS  = -ggdb -MMD -Wall -Werror -Wshadow -Weffc++ -pedantic -std=c++17 -O2
CPPLFLAGS = -lreadline

phipsshell: $(OBJ)
	$(CC) $(LINK_DIRS) $(CPPFLAGS) -o $@ $+ $(CPPLFLAGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(INC_DIRS) $(CPPFLAGS) -c -o $@ $<


.PHONY: install
install: phipsshell
	install -d $(DESTDIR)/bin
	install -m 755 $< $(DESTDIR)/bin

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) phipsshell bin

# follow dependency files (to trigger recompile if file changed)
-include $(DEP)
