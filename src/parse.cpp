#include <cstring>
#include <zconf.h>
#include "parse.hpp"
#include "strings.hpp"
#include "alias.hpp"

ParsedInputData parse(std::string const * const normalized_input) {
    ParsedInputData data;
    if (*normalized_input == "exit") {
        data.setType(InputKind::EXIT);
    } else if (normalized_input->empty()) {
        data.setType(InputKind::EMPTY);
    } else if (is_cd_input(normalized_input)) {
        data.setType(InputKind::CD);
        // TODO get data and put it into the object
    } else if (is_un_alias_input(normalized_input)) {
        data.setType(InputKind::UN_ALIAS);
        // TODO get data and put it into the object
    } else if (is_get_alias_input(normalized_input)) {
        data.setType(InputKind::GET_ALIAS);
        // TODO get data and put it into the object
    } else if (is_set_alias_input(normalized_input)) {
        data.setType(InputKind::SET_ALIAS);
        // TODO get data and put it into the object
    }
    else {
        data.setType(InputKind::UNKNOWN);
    }
    return data;
}

bool is_un_alias_input(const std::string *const input) {
    if (!str_starts_with(input, &UN_ALIAS_COMMAND_PREFIX)) {
        return false;
    }
    if (input->length() <= UN_ALIAS_COMMAND_PREFIX.length()) {
        fprintf(stderr, "Syntax is: unalias <alias-name>\n");
        return false;
    }
    if (!str_contains_single_word_from_to(
            input,
            UN_ALIAS_COMMAND_PREFIX.length() + 1, // skip space
            input->length() - 1)) {
        // name of alias not is given
        fprintf(stderr, "Syntax is: unalias <alias-name>\n");
        return false;
    }
    return true;
}

bool is_set_alias_input(const std::string *const input) {
    if (!str_starts_with(input, &SET_ALIAS_COMMAND_PREFIX)) {
        return false;
    }
    if (input->length() <= SET_ALIAS_COMMAND_PREFIX.length()) {
        fprintf(stderr, "Syntax is: alias <alias-name>=<alias-value>\n");
        return false;
    }

    unsigned eq_sign_i = input->find('=');
    if (eq_sign_i == -1u) {
        fprintf(stderr, "Syntax is: alias <alias-name>=<alias-value>\n");
        return false;
    }

    // check if contains key
    if (!str_contains_single_word_from_to(
            input,
            SET_ALIAS_COMMAND_PREFIX.length() + 1, // skip space
            eq_sign_i)) {
        // name of alias not given
        fprintf(stderr, "Syntax is: alias <alias-name>=<alias-value>\n");
        return false;
    }

    // check if not contains value; -1 because array indices starts at 0
    if (eq_sign_i >= (input->length() - 1)) {
        // value of alias not given
        fprintf(stderr, "Syntax is: alias <alias-name>=<alias-value>\n");
        return false;
    }

    return true;
}

bool is_get_alias_input(const std::string *const input) {
    if (!str_starts_with(input, &GET_ALIAS_COMMAND_PREFIX)) {
        return false;
    }
    if (input->length() <= GET_ALIAS_COMMAND_PREFIX.length()) {
        fprintf(stderr, "Syntax is: getalias <alias-name>\n");
        return false;
    }
    if (!str_contains_single_word_from_to(
            input,
            GET_ALIAS_COMMAND_PREFIX.length() + 1, // skip space
            input->length() - 1)) {
        // name of alias not is given
        fprintf(stderr, "Syntax is: getalias <alias-name>\n");
        return false;
    }
    return true;
}

bool is_command_input(const std::string *const input) {
    return false;
}

bool is_cd_input(const std::string *const input) {
    char const * const c_str = input->c_str();
    // check if it begins with "cd"
    if (strncmp(c_str, "cd", 2) == 0 && c_str[2] == ' ') {
        // check if string is not ending here
        if (&c_str[3] == nullptr) {
            fprintf(stderr, "Please enter a directory for cd!\n");
        }
        // decoupling parsing and performing action
        //else chdir(&c_str[3]);
        return true;
    }
    return false;
}
