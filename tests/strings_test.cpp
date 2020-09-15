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

    // test str_starts_with
    std::string haystack = "foobar";
    std::string needle = "foo";
    std::string needle2 = "oobar";
    assert(str_starts_with(&haystack, &needle));
    assert(!str_starts_with(&haystack, &needle2));

    // test str_contains_single_word_from_to()
    std::string value = "cd whatever123 afaf";
    assert(str_contains_single_word_from_to(&value, 3, 14));
    assert(!str_contains_single_word_from_to(&value, 3, 15));
    assert(str_contains_single_word_from_to(&value, 15, 19)); // last index is exclusive, first inclusive

    return 0;
}
