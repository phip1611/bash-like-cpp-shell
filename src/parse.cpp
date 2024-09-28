/*
 * Copyright 2020 - Philipp Schuster.
 *
 * This file/project is licensed under a MIT license.
 * You can find the LICENSE file in the repository.
 */

// All functions related to verifying and parsing the input.

#include <cstring>
#include <sstream>
#include <unistd.h>
#include <dirent.h>

#include "parse.hpp"
#include "strings.hpp"
#include "alias.hpp"

ParsedInputData parse(std::string const * const normalized_input) {
    ParsedInputData data;
    try {
        if (*normalized_input == "exit") {
            data.setType(InputKind::EXIT);
        } else if (normalized_input->empty()) {
            data.setType(InputKind::EMPTY);
        } else if (verify_is_cd_input(normalized_input)) {
            data.setType(InputKind::CD);
            data.setDataCdDir(
                    std::optional(
                            parse_cd_data(normalized_input)
                    )
            );
        } else if (verify_is_un_alias_input(normalized_input)) {
            data.setType(InputKind::UN_ALIAS);
            // TODO get data and put it into the object
        } else if (verify_is_get_alias_input(normalized_input)) {
            data.setType(InputKind::GET_ALIAS);
            // TODO get data and put it into the object
        } else if (verify_is_set_alias_input(normalized_input)) {
            data.setType(InputKind::SET_ALIAS);
            // TODO get data and put it into the object
        } else if (verify_is_command_input(normalized_input)) {
            data.setType(InputKind::COMMAND);
            data.setDataCommandChain(
                    parse_command_chain(normalized_input)
            );
        } else {
            data.setType(InputKind::UNKNOWN);
        }
    } catch (std::exception & e) {
        std::cerr << "Error during parsing of command: Input type unknown!" << std::endl;
        data.setType(InputKind::UNKNOWN);
    }

    return data;
}

bool verify_is_un_alias_input(const std::string *const input) {
    if (!str_starts_with(input, &UN_ALIAS_COMMAND_PREFIX)) {
        return false;
    }
    if (input->length() <= UN_ALIAS_COMMAND_PREFIX.length()) {
        fprintf(stderr, "Syntax is: unalias <alias-name>\n");
        return false;
    }

    // check if alias name is given
    if (!str_contains_single_word_from_to(
            input,
            UN_ALIAS_COMMAND_PREFIX.length() + 1, // skip space
            input->length())) {
        // name of alias not is given
        fprintf(stderr, "Syntax is: unalias <alias-name>\n");
        return false;
    }

    // check alias name format
    if (!str_contains_only_given_chars(input,
                                       UN_ALIAS_COMMAND_PREFIX.length() + 1, // skip space
                                       input->length(),
                                       &GET_ALIAS_NAME_ALLOWED_CHARS)) {
        // format of alias illegal
        fprintf(stderr, "Syntax is: unalias <alias-name>\n");
        return false;
    }

    return true;
}

bool verify_is_set_alias_input(const std::string *const input) {
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

    // check key format
    if (!str_contains_only_given_chars(input,
                                       SET_ALIAS_COMMAND_PREFIX.length() + 1, // skip space
                                       eq_sign_i,
                                       &GET_ALIAS_NAME_ALLOWED_CHARS)) {
        // format of alias illegal
        fprintf(stderr, "Syntax is: alias <alias-name>=<alias-value>\n");
        return false;
    }


    // check if not contains value; -1 because array indices starts at 0
    if (eq_sign_i >= (input->length() - 1)) {
        // value of alias not given
        fprintf(stderr, "Syntax is: alias <alias-name>=<alias-value>\n");
        return false;
    }

    // check value format
    if (!str_contains_only_given_chars(input,
                                       eq_sign_i + 1,
                                       input->length(),
                                       &SET_ALIAS_VALUE_ALLOWED_CHARS)) {
        // format of alias illegal
        fprintf(stderr, "Syntax is: alias <alias-name>=<alias-value>\n");
        return false;
    }

    return true;
}

bool verify_is_get_alias_input(const std::string *const input) {
    if (!str_starts_with(input, &GET_ALIAS_COMMAND_PREFIX)) {
        return false;
    }
    if (input->length() <= GET_ALIAS_COMMAND_PREFIX.length()) {
        fprintf(stderr, "Syntax is: getalias <alias-name>\n");
        return false;
    }
    // check if alias name is given
    if (!str_contains_single_word_from_to(
            input,
            GET_ALIAS_COMMAND_PREFIX.length() + 1, // skip space
            input->length())) {
        // name of alias not given
        fprintf(stderr, "Syntax is: getalias <alias-name>\n");
        return false;
    }


    // check alias name format
    if (!str_contains_only_given_chars(input,
                                      GET_ALIAS_COMMAND_PREFIX.length() + 1, // skip space
                                      input->length(),
                                      &GET_ALIAS_NAME_ALLOWED_CHARS)) {
        // format of alias illegal
        fprintf(stderr, "Syntax is: getalias <alias-name>\n");
        return false;
    }

    return true;
}

bool verify_is_command_input(const std::string *const input) {
    // Because I'm not a regex expert, std::regex is limited, and I don't
    // want to use "boost" as another dependency, I just don't do really
    // verifying at all. Focus here is on valid user input anyway. :)
    return input->length() > 0;
}

bool verify_is_cd_input(const std::string *const input) {
    char const * const c_str = input->c_str();
    // check if it begins with "cd"
    if (strncmp(c_str, "cd", 2) == 0 && c_str[2] == ' ') {
        // check if string is not ending here
        if (c_str[3] == '\0') {
            fprintf(stderr, "Please enter a directory for cd!\n");
        }
        // decoupling parsing and performing action
        //else chdir(&c_str[3]);
        return true;
    }
    return false;
}

std::string parse_cd_data(const std::string *const input) {
    std::string dir;
    // "cd foobar" => "cd "^ => index 3
    for (unsigned i = 3; i < input->length(); i++) {
        dir.push_back((*input)[i]);
    }
    return dir;
}

CommandChain parse_command_chain(const std::string *const input) {
    // first split into all basic parts (without pipe symbol)

    CommandChain commandChain;

    std::vector<Command> basic_commands;
    std::vector<std::string> basic_command_strs = str_split_char(input, '|');
    for (auto & basic_command_str : basic_command_strs) {
        trim(basic_command_str);
        // we want to trim the strings because "ls | cat" splitted by '|' would otherwise
        // have spaces at the begin/end
    }

    for (unsigned i = 0; i < basic_command_strs.size(); i++) {
        basic_commands.push_back(
                parse_command_chain_command(
                        &basic_command_strs[i],
                        i,
                        basic_command_strs.size()
                )
        );
    }

    commandChain.setBasicCommands(basic_commands);

    // check background
    // because our string is normalized (trimmed) it's easy
    // either the last character is '&' or not
    commandChain.setBackground(input->back() == '&');

    return commandChain;
}

Command parse_command_chain_command(const std::string *const input, unsigned i, unsigned n) {
    Command cmd;

    cmd.setIsBegin(i == 0);
    cmd.setIsEnd(i + 1 == n);

    // at this point input might be something like "cat < foobar.txt" or "ls -la"

    // we made sure that there are no "  " (double spaces)
    // therefore we can safely do a spring split know
    std::vector<std::string> basic_command_string_parts = str_split_char(input, ' ');

    // the actual command, like "ls" or "cat"
    std::string & basic_command_string_cmd = basic_command_string_parts[0];

    // could be: ['ls', '-l']
    cmd.setArgs(
            parse_command_chain_command_args(basic_command_string_parts)
    );

    // this is "ls", "cat", "./mybin" or "/usr/bin/bash" for example
    if (check_executable_path_exists(&basic_command_string_cmd)) {
        cmd.setExecutable(basic_command_string_cmd);
    } else {
        std::cerr << "Can't find executable path for command '" << basic_command_string_cmd << "'" << std::endl;
        throw std::exception();
    }

    parse_command_chain_command_io_redirection(cmd, input);
    return cmd;
}

void parse_command_chain_command_io_redirection(Command & cmd, const std::string * const basic_command_str) {
    // only supported if:
    // input file && is first
    // output file && is last
    if (cmd.is_in_middle()) return;

    for (unsigned i = 0; i < basic_command_str->size(); i++) {
        char c = (*basic_command_str)[i];
        // actually one could do some more checking here, like
        // if cmd.pos == BEGIN and c == '<' but I wanted to decouple the
        // verifying and parsing check.. i.e.: if something terribly wrong
        // happens here it's the fault of a bad verifying step

        if (c == '<' || c == '>') {
            std::string file = basic_command_str->substr(i + 1);
            trim(file);
            if (c == '<') {
                cmd.setInputRedFile(file);
            } else {
                cmd.setOutputRedFile(file);
            }
        }
    }
}

std::vector<std::string> parse_command_chain_command_args(std::vector<std::string> & basic_command_string_parts) {
    std::vector<std::string> args = {};

    for (auto & str : basic_command_string_parts) {
        // i/o redirect and background are no args for the program but
        // hints for the shell
        if (str[0] == '<' || str[0] == '>' || str[0] == '&') {
            break;
        } else {
            args.push_back(str);
        }
    }

    return args;
}

bool check_executable_path_exists(std::string * command) {
    std::string local_path_prefix = "./";
    std::string parent_path_prefix = "../";

    // relative path or absolute path
    if ((*command)[0] == '/' || str_starts_with(command, &local_path_prefix) || str_starts_with(command, &parent_path_prefix)) {
        return access(command->c_str(), F_OK | X_OK) != -1;
    }

    // otherwise search in path
    std::string path_var = getenv("PATH"); // calls the string constructor which creates a copy
    std::vector<std::string> path_var_parts = str_split_char(&path_var, ':');

    for (auto & part : path_var_parts) {
        DIR * d = opendir(part.c_str());
        if (d == nullptr) {
            // protect against malformed path
            // e.g. "foobar//something"
            continue;
        }
        struct dirent * direntry;
        while ((direntry = readdir(d)) != nullptr) {
            // skip '.' and '..'
            if ((direntry->d_name[0] == '.' && direntry->d_name[1] == '\0')
                || (direntry->d_name[0] == '.' && direntry->d_name[1] == '.' && direntry->d_name[2] == '\0')) {
                continue;
            }

            // exists
            if (strcmp(direntry->d_name, command->c_str()) == 0) {
                return true;
            }
        }
        closedir(d);
    }

    return false;
}

