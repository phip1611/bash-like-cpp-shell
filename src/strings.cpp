/*
 * Copyright 2020 - Philipp Schuster.
 *
 * This file/project is licensed under a MIT license.
 * You can find the LICENSE file in the repository.
 */

// String utility functions

#include <sstream>
#include <cassert>
#include <cstring>

#include "strings.hpp"

std::string normalize_input(char const * const input) {
    size_t spaces_at_begin = 0;
    size_t spaces_at_end = 0;
    size_t str_len = 0;

    assert(input != nullptr);
    str_len = strlen(input);
    for (size_t i = 0; i < str_len; i++) {
        if (input[i] == ' ') {
            spaces_at_begin++;
        } else {
            break;
        }
    }

    for (size_t i = 0; i < str_len; i++) {
        size_t i_rev = str_len - 1 - i; // reversed iteration; backwards
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

    size_t space_count = 0;
    for (size_t i = spaces_at_begin; i < str_len - spaces_at_end; i++) {
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

bool str_contains_single_word_from_to(const std::string *const input, size_t from, size_t to) {
    assert(from <= to);
    assert(to <= input->length());
    // assert(from <= input->length()); already proved because of the partial order of from, to and input length :)
    for (size_t i = from; i < to; i++) {
        char c = (*input)[i];
        if (c == ' ') {
            // if space found
            return false;
        }
    }
    return true;
}

bool str_contains_only_given_chars(const std::string *const input, size_t from, size_t to,
                                   const std::string *const chars) {
    assert(from <= to);
    assert(to <= input->length());

    for (size_t i = from; i < to; i++) {
        bool found_current_char_in_allowed_chars = false;
        char const c = (*input)[i];
        for (size_t j = 0; j < chars->length(); j++) {
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

std::vector<std::string> str_split_str(const std::string *s, const std::string &delim) {
    // code from https://stackoverflow.com/a/46931770/2891595
    size_t pos_start = 0, pos_end, delim_len = delim.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s->find (delim, pos_start)) != std::string::npos) {
        token = s->substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s->substr (pos_start));
    return res;
}

std::vector<std::string> str_split_char(const std::string *s, char const delim) {
    // code from https://stackoverflow.com/a/46931770/2891595
    std::vector<std::string> res;
    std::stringstream ss (*s);
    std::string item;

    while (std::getline(ss, item, delim)) {
        res.push_back (item);
    }
    return res;
}

void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

// trim from start (in place)
// https://stackoverflow.com/a/44973498/2891595
void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
// https://stackoverflow.com/a/44973498/2891595
void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// currently unused but perhaps useful in future if better validation code comes
// or a good regex that actually works properly
/* bool str_regex_is_full_match(const std::string &str, const std::regex &regex) {
    std::smatch m;
    bool found;
    try {
        found = std::regex_match(str, m, regex);
    } catch (std::exception &e) {
        // could result in "The complexity of an attempted match against a
        // regular expression exceeded a pre-set level"
        // this is because std::regex "is bad" and lib boost should be used
        //std::cerr << e.what() << std::endl;
    }

    // std::cout << "found?: " << found << std::endl;
    if (found) {
        std::cout << "length of string: " << haystack.length() << std::endl;
        std::cout << "length of match: " << m.length() << std::endl;
    }

    return found && str.length() == m.length();
}*/
