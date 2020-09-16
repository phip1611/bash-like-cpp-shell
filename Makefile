SRC_DIR = src
OBJ_DIR = build

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEP = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.d)

# don't worry; because of debug symbols the binary get's up to 2MB larger than in my
# previous C project; with -O2 (or O3) additional 2 MB bin size
CPPFLAGS  = -MMD -Wall -Werror -Wshadow -Weffc++ -pedantic -std=c++17 -O3
CPPLFLAGS = -lreadline

phipsshell: $(OBJ)
	g++ $(CPPFLAGS) -o $@ $+ $(CPPLFLAGS)

                               # | is a dependency; create if doesn't exist
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	g++ $(CPPFLAGS) -c -o $@ $<

# if OBJ_DIR doesn't exist: create
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

.PHONY: clean

clean:
	rm -rf $(OBJ_DIR) phipsshell

# follow dependency files (to trigger recompile if file changed)
-include $(DEP)
