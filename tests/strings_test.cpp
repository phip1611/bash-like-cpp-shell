#include <cassert>
#include <cstring>
#include <alias.hpp>
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

    // test str_contains_only_given_chars()
    std::string teststr = "alias l=ls -la";
    // 'l'
    assert(str_contains_only_given_chars(&teststr, 6, 7, &GET_ALIAS_NAME_ALLOWED_CHARS));
    // '='
    assert(!str_contains_only_given_chars(&teststr, 7, 8, &GET_ALIAS_NAME_ALLOWED_CHARS));
    // 'ls -la'
    assert(!str_contains_only_given_chars(&teststr, 8, 14, &GET_ALIAS_NAME_ALLOWED_CHARS));
    // 'ls -la'
    assert(str_contains_only_given_chars(&teststr, 8, 14, &SET_ALIAS_VALUE_ALLOWED_CHARS));

    // test str_regex_is_full_match()
    std::string haystack2 = "../foobar/../foobar < in.txt | ../foobar/../foobar > out.txt &";
    assert(str_regex_is_full_match(haystack2, std::regex("(((\\/?\\.{0,2}\\/?)+[A-z0-9ÄÖÜäöü])+\\s?(\\<|\\>\\s?)?\\|?\\s?)+\\&?")));
    assert(str_regex_is_full_match("foobar", std::regex("foobar")));
    assert(!str_regex_is_full_match("foobarfoobar", std::regex("foobar")));

    return 0;
}
