SRC_DIR = src
OBJ_DIR = build

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEP = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.d)

CPPFLAGS  = -ggdb -MMD -Wall -Werror -Wshadow -Weffc++ -pedantic -std=c++17
CPPLFLAGS = -lreadline

phipsshell: $(OBJ)
	g++ $(CPPFLAGS) -o $@ $+ $(CPPLFLAGS)

                                      # | is a dependency; create if doesn't exist
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp Makefile | $(OBJ_DIR)
	g++ $(CPPFLAGS) -c -o $@ $<

# if OBJ_DIR doesn't exist: create
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

.PHONY: clean

clean:
	rm -rf $(OBJ_DIR) phipsshell

# follow dependency files (to trigger recompile if file changed)
-include $(DEP)
