#include <cstring>
#include <dirent.h>
#include "parse.hpp"
#include "strings.hpp"
#include "alias.hpp"

std::regex COMMAND_CHAIN_VERIFY_REGEX("([A-z0-9ÄÖÜäöü/]+\\s?\\<?\\s?\\>?[A-z0-9-ÄÖÜäöü\\./]*\\s?\\>?\\s?\\|?\\s?\\>?)+(\\&)?");


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
                    parse_command_data(normalized_input)
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
    return input->length() > 0 && regex_match(*input, COMMAND_CHAIN_VERIFY_REGEX);
}

bool verify_is_cd_input(const std::string *const input) {
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

std::string parse_cd_data(const std::string *const input) {
    std::string dir;
    // "cd foobar" => "cd "^ => index 3
    for (unsigned i = 3; i < input->length(); i++) {
        dir.push_back((*input)[i]);
    }
    return dir;
}

CommandChain parse_command_data(const std::string *const input) {
    // first split into all basic parts (without pipe symbol)

    CommandChain commandChain;

    std::vector<Command> basic_commands;
    std::vector<std::string> basic_command_strs = str_split_char(input, '|');
    for (unsigned i = 0; i < basic_command_strs.size(); i++) {
        trim(basic_command_strs[i]);
        // we want to trim the strings because "ls | cat" splitted by '|' would otherwise
        // have spaces at the begin/end
    }
    CommandPosition pos;

    for (unsigned i = 0; i < basic_command_strs.size(); i++) {
        if (i == 0) {
            pos = BEGIN;
        } else if (i == basic_command_strs.size() - 1) {
            pos = END;
        } else {
            pos = IN_THE_MIDDLE;
        }
        basic_commands.push_back(
                parse_basic_command_data(
                        &basic_command_strs[i],
                        pos
                )
        );
    }

    commandChain.setBasicCommands(basic_commands);
    commandChain.setBackground(false); // TODO

    return commandChain;
}

Command parse_basic_command_data(const std::string *const input, CommandPosition pos) {
    Command cmd;
    cmd.setPosition(pos);

    // at this point input might be something like "cat < foobar.txt" or
    // "ls -la"

    // we made sure that there are no "  " (double spaces)
    // therefore we can safely do a spring split know
    std::vector<std::string> basic_command_string_parts = str_split_char(input, ' ');

    // the actual command, like "ls" or "cat"
    std::string & basic_command_string_cmd = basic_command_string_parts[0];


    // Okay this is my old legacy code from my old C shell
    // TODO make cool C++ code

    // Berechnen aus wie vielen Teilen der String besteht anhand des String Splittings an " "
    // haben vorher bereits getrimmt und dafür gesorgt dass keine Ketten von " " vorkommen!
    /*char * * str_parts_walker_ptr;
    char * * cmd_str_parts = str_split(string, " "); // gibt nullterminiertes array zurück

    do {
        b_cmd->command = strdup(cmd_str_parts[0]);
        b_cmd->executable = get_executable_path(b_cmd->command);
        if (b_cmd->executable == NULL) {
            fprintf(stderr, "Command '%s' not Found in PATH!\n", b_cmd->command);
            free_basic_cmd(b_cmd);
            b_cmd = NULL;
            break;
        }

        // argc setzen und argv aufbauen
        // str_parts_walker_ptr zeigt nun auf das ende der args: eventuell ist ein input redirect zu finden?
        str_parts_walker_ptr = parse_basic_command_args(cmd_str_parts, b_cmd);


        if (number == 0) {
            // das erste Kommando darf einen input_redirect haben
            int succ = parse_basic_command_redirect(INPUT_REDIRECT, b_cmd, &str_parts_walker_ptr);
            if (succ != 0) {
                free_basic_cmd(b_cmd);
                b_cmd = NULL;
                break;
            }
        }

        if (is_last) {
            // das letzte Kommando darf einen output_redirect haben
            int succ = parse_basic_command_redirect(OUTPUT_REDIRECT, b_cmd, &str_parts_walker_ptr);
            if (succ != 0) {
                free_basic_cmd(b_cmd);
                b_cmd = NULL;
                break;
            }
        }
    } while (NULL);



    // alle cmd_str_parts wieder freigeben
    free_str_arr(&cmd_str_parts);
    return b_cmd;*/


    std::vector<std::string> dummy_args = {"dummy", "-l", "a"};
    // TODO
    cmd.setArgs(dummy_args);
    std::optional<std::string> path = get_executable_path(&basic_command_string_cmd);
    if (!path.has_value()) {
        std::cerr << "Can't find executable path for command '" << basic_command_string_cmd << "'" << std::endl;
        throw std::exception();
    } else {
        cmd.setExecutablePath(path.value());
    }
    cmd.setCommand(basic_command_string_cmd);
    return cmd;
}

std::optional<std::string> get_executable_path(std::string * command) {
    std::optional<std::string> path = std::nullopt;

    std::string local_path_prefix = "./";
    std::string parent_path_prefix = "../";

    // relative path or absolute path
    if ((*command)[0] == '/' || str_starts_with(command, &local_path_prefix) || str_starts_with(command, &parent_path_prefix)) {
        std::string cpy = *command;  // creates a copy
        path.emplace(cpy);
        return path;
    }

    // otherwise search in path
    std::string path_var = getenv("PATH"); // calls the string constructor which creates a copy
    std::vector<std::string> path_var_parts = str_split_char(&path_var, ':');

    for (auto & part : path_var_parts) {
        DIR * d = opendir(part.c_str());
        struct dirent * direntry;
        while ((direntry = readdir(d)) != nullptr) {
            // skip '.' and '..'
            if ((direntry->d_name[0] == '.' && &direntry->d_name[1] == nullptr)
                    || (direntry->d_name[0] == '.' && direntry->d_name[1] == '.' && &direntry->d_name[2] == nullptr)) {
                continue;
            }

            if (strcmp(direntry->d_name, command->c_str()) == 0) {
                std::ostringstream stringStream;
                stringStream << part << '/' << *command;
                path.emplace(stringStream.str()); // creates a copy
                break;
            }
        }
        closedir(d);
    }

    return path;
}

/*int parse_basic_command_redirect(REDIRECT red, basic_cmd *b_cmd, char *** str_parts_walker_ptr) {
    char c = (char) (red == INPUT_REDIRECT ? '<' : '>');

    // neue Variable damit das mit dem Dreifachen Pointer nicht überhand nimmt.
    // erste dereferenzierung: das eigentliche char array (char **): zeigt konkret auf das Element des Array
    //                         das als nächstes zu parsen ist
    // zweite dereferenzierung: der String auf den gerade gezeigt wird
    char ** current_str_ptr = *str_parts_walker_ptr;

    if (*current_str_ptr != NULL) {
        // es gibt beim Pointer noch etwas: Input/Output Redirect (oder invalide Eingabe)
        if (**current_str_ptr == c) {
            // ist ein input oder output redirect; gibt es noch das passende argument?
            if (*(current_str_ptr + 1) != NULL) {
                if (red == INPUT_REDIRECT) {
                    b_cmd->input_red  = strdup(*(current_str_ptr + 1)); // nach '<' steht bspw. file.txt
                } else {
                    b_cmd->output_red = strdup(*(current_str_ptr + 1)); // nach '>' steht bspw. file.txt
                }
                *str_parts_walker_ptr += 2; // Den Pointer auf dem Array weiter schieben bis dahin wo nun geparst wurde
                return 0;
            } else {
                fprintf(stderr, "%s Redirect ohne Parameter!\n", red == INPUT_REDIRECT ? "Input" : "Output");
                return -1;
            }
        } else {
            return 0; // alles ok, könnte bspw. ein '&' (Disown) sein
        }
    }
    return 0;
}*/

/*char ** parse_basic_command_args(char **cmd_str_parts, basic_cmd * b_cmd) {
    // argv und argc aufbauen
    int argc = 0;
    char * * str_parts_walker_ptr;
    str_parts_walker_ptr = cmd_str_parts;
    while(*str_parts_walker_ptr != NULL  // Ende des Nullterminierten Arrays finden
          // erstmal nur anzahl argumente zählen, um im nöchsten schritt das argv array aufbauen zu können
          && **str_parts_walker_ptr != '<'
          && **str_parts_walker_ptr != '>'
          && **str_parts_walker_ptr != '&') {
        argc++;
        str_parts_walker_ptr++;
    }
    b_cmd->argc = argc;
    b_cmd->argv = calloc((size_t) argc + 1, sizeof(char *)); // + 1: Null terminated!!
    b_cmd->argv[0] = strdup(b_cmd->command); // bei Unix ist der erste Parameter der Name wie das Programm aufgerufen wurde
    int argc_i = 1;
    str_parts_walker_ptr = cmd_str_parts + 1; // &cmd_str_parts[1]
    // Alle Parameter durchwalken; Nullterminiertes Array
    while (*str_parts_walker_ptr != NULL // Ende des Nullterminierten Arrays finden
           && **str_parts_walker_ptr != '<'
           && **str_parts_walker_ptr != '>'
           && **str_parts_walker_ptr != '&') {
        b_cmd->argv[argc_i++] = strdup(*str_parts_walker_ptr);
        str_parts_walker_ptr++;
    }
    return str_parts_walker_ptr;
}*/
