/*
 * Copyright 2020 - Philipp Schuster.
 *
 * This file/project is licensed under a MIT license.
 * You can find the LICENSE file in the repository.
 */

// Command class.

#include <sstream>
#include <optional>

#include "command.class.hpp"
#include "command-position.enum.hpp"

const std::string &Command::getExecutable() const {
    return executable;
}

const std::vector<std::string> &Command::getArgs() const {
    return args;
}

const std::optional<std::string> &Command::getInputRedFile() const {
    return input_red_file;
}

const std::optional<std::string> &Command::getOutputRedFile() const {
    return output_red_file;
}

void Command::setExecutable(const std::string &executableNew) {
    Command::executable = executableNew;
}

void Command::setArgs(const std::vector<std::string> &argsNew) {
    Command::args = argsNew;
}

void Command::setInputRedFile(const std::optional<std::string> &inputRedFileNew) {
    input_red_file = inputRedFileNew;
}

void Command::setOutputRedFile(const std::optional<std::string> &outputRedFileNew) {
    output_red_file = outputRedFileNew;
}

CommandPosition Command::getPosition() const {
    return position;
}

void Command::setPosition(CommandPosition positionNew) {
    Command::position = positionNew;
}

char ** Command::build_argv() const {
    // +1 -> null terminated
    char ** argv = static_cast<char **>(calloc(sizeof(char *), this->getArgs().size() + 1));
    for (unsigned i = 0; i < this->getArgs().size(); i++) {
        argv[i] = strdup(this->getArgs()[i].data());
    }
    return argv;
}

std::string Command::toString() {
    std::ostringstream stringStream;
    stringStream << "Command {\n";
    stringStream << "          executable: " << this->executable << "\n";
    stringStream << "          position: " << command_position::to_string(this->position) << "\n";
    stringStream << "          args:\n";

    for (unsigned i = 0; i < this->args.size(); i++) {
        stringStream << "            [" << i << "]" << this->args[i] << "\n";
    }

    stringStream << "          input_red_file: ";
    if (this->input_red_file.has_value()) {
        stringStream << this->input_red_file.value() << "\n";
    } else {
        stringStream << "<none>\n";
    }

    stringStream << "          output_red_file: ";
    if (this->output_red_file.has_value()) {
        stringStream << this->output_red_file.value() << "\n";
    } else {
        stringStream << "<none>\n";
    }

    stringStream << "        }";

    return stringStream.str(); // creates a copy
}
