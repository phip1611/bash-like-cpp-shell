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

# Mac OS specific
# only use the libreadline header files in this repository
# if on MacOS/Darwin. Otherwise use the ones that have been
# installed via package manager in linux distribution (most recent ones)
# the reason for this is: `brew install readline` doesn't
# install header files
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	INC_DIRS=-I./include
	LINK_DIRS=-L/usr/local/opt/readline/lib/ # location where brew installs readline
endif
# End: Mac OS specific

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
	rm -rf $(OBJ_DIR) phipsshell

# follow dependency files (to trigger recompile if file changed)
-include $(DEP)
