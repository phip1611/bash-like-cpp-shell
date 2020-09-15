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

bool str_starts_with(std::string const * const haystack, std::string const * const needle) {
    if (haystack->rfind(*needle, 0) == 0) {
        return true;
    }
    return false;
}

bool str_contains_single_word_from_to(const std::string *const input, unsigned from, unsigned to) {
    assert(from <= to);
    assert(to <= input->length());
    // assert(from <= input->length()); already proved because of the partial order of from, to and input length :)
    for (unsigned i = from; i < to; i++) {
        char c = (*input)[i];
        if (c == ' ') {
            // if space found
            return false;
        }
    }
    return true;
}

bool str_contains_only_given_chars(const std::string *const input, unsigned int from, unsigned int to,
                                   const std::string *const chars) {
    assert(from <= to);
    assert(to <= input->length());

    for (unsigned i = from; i < to; i++) {
        bool found_current_char_in_allowed_chars = false;
        char const c = (*input)[i];
        for (unsigned j = 0; j < chars->length(); j++) {
            char const allowed_char = (*chars)[j];
            if (c == allowed_char) {
                found_current_char_in_allowed_chars = true;
                break;
            }
        }
        if (!found_current_char_in_allowed_chars) {
            return false;
        }
    }

    return true;
}
