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

CPPFLAGS  = \
	-std=c++23 -ggdb -O3 \
	-U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=3 -D_GLIBCXX_ASSERTIONS \
	-Wall -Wformat -Wformat=2 -Wconversion -Wimplicit-fallthrough \
	-Werror=format-security -Wpedantic -pedantic \
	-Wextra -Wcast-align -Wcast-qual -Wdisabled-optimization \
	-Wduplicated-branches -Wduplicated-cond -Wlogical-op \
	-Wnull-dereference -Woverloaded-virtual -Wpointer-arith  \
	-fcf-protection=return \
	-Wshadow -Weffc++ -Wswitch-enum -Wvla -Wuseless-cast \
	-Wl,-z,nodlopen -Wl,-z,noexecstack -Wl,-z,relro -Wl,-z,now \
    -Wl,--as-needed -Wl,--no-copy-dt-needed-entries
CPPLFLAGS = -lreadline

phipsshell: $(OBJ)
	$(CC) $(LINK_DIRS) $(CPPFLAGS) -o $@ $+ $(CPPLFLAGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(INC_DIRS) $(CPPFLAGS) -c -o $@ $<

#.PHONY: test
#test:
#	$(MAKE) -C tests

.PHONY: install
install: phipsshell
	install -d $(DESTDIR)/bin
	install -m 755 $< $(DESTDIR)/bin

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) phipsshell bin

# follow dependency files (to trigger recompile if file changed)
-include $(DEP)
