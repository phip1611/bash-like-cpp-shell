#include <cassert>
#include <cstring>
#include "strings.hpp"

constexpr int NUM_ELEMENTS = 5;

int main() {
    std::string inputs[NUM_ELEMENTS];
    std::string expected[NUM_ELEMENTS];

    inputs[0] = "";
    expected[0] = "";
    inputs[1] = "     ";
    expected[1] = "";
    inputs[2] = "   foo";
    expected[2] = "foo";
    inputs[3] = "bar   ";
    expected[3] = "bar";
    inputs[4] = "   foo      bar   ";
    expected[4] = "foo bar";

    for (int i = 0; i < NUM_ELEMENTS; i++) {
        std::string actual = normalize_input(inputs[i].c_str());
        if (expected[i] != actual) {
            std::cerr << "'" << expected[i]  << "' (expected) != (actual) '" << actual << "'" << std::endl;
            return -1;
        }
    }

    return 0;
}
