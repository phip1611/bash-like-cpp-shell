#include <cassert>
#include <cstring>
#include "strings.hpp"

std::string normalize_input(char const * const input) {
    int spaces_at_begin = 0;
    int spaces_at_end = 0;
    int str_len = 0;

    assert(input != nullptr);
    str_len = strlen(input);
    for (int i = 0; i < str_len; i++) {
        if (input[i] == ' ') {
            spaces_at_begin++;
        } else {
            break;
        }
    }

    for (int i = 0; i < str_len; i++) {
        int i_rev = str_len - 1 - i; // reversed iteration; backwards
        if (input[i_rev] == ' ') {
            spaces_at_end++;
        } else {
            break;
        }
    }

    // return if string is empty or contains only spaces
    // str_len == spaces_at_begin  is alias of == spaces_at_end in the case of only spaces
    if (str_len == 0 || str_len == spaces_at_begin ) {
        return "";
    }

    std::string str;
    str.reserve(str_len - spaces_at_begin - spaces_at_end);

    int space_count = 0;
    for (int i = spaces_at_begin; i < str_len - spaces_at_end; i++) {
        char c = input[i];
        if (c == ' ') {
            space_count++;
        } else {
            space_count = 0;
        }

        if (space_count <= 1) {
            str.push_back(input[i]);
        }
    }

    return str;
}
