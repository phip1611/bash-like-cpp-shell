/*
 * Copyright 2020 - Philipp Schuster.
 *
 * This file/project is licensed under a MIT license.
 * You can find the LICENSE file in the repository.
 */

// Command class.

#include <cstring>
#include <optional>
#include <sstream>

#include "command.class.hpp"

const std::string& Command::getExecutable() const {
  return executable;
}

const std::vector<std::string>& Command::getArgs() const {
  return args;
}

const std::optional<std::string>& Command::getInputRedFile() const {
  return input_red_file;
}

const std::optional<std::string>& Command::getOutputRedFile() const {
  return output_red_file;
}

void Command::setExecutable(const std::string& executableNew) {
  Command::executable = executableNew;
}

void Command::setArgs(const std::vector<std::string>& argsNew) {
  Command::args = argsNew;
}

void Command::setInputRedFile(
    const std::optional<std::string>& inputRedFileNew) {
  input_red_file = inputRedFileNew;
}

void Command::setOutputRedFile(
    const std::optional<std::string>& outputRedFileNew) {
  output_red_file = outputRedFileNew;
}

char** Command::build_argv() const {
  // +1 -> null terminated
  char** argv =
      static_cast<char**>(calloc(sizeof(char*), this->getArgs().size() + 1));
  for (unsigned i = 0; i < this->getArgs().size(); i++) {
    argv[i] = strdup(this->getArgs()[i].data());
  }
  return argv;
}

bool Command::is_in_middle() const {
  return !this->is_begin && !this->is_end;
}

bool Command::is_last() const {
  return this->is_end;
}

bool Command::is_first() const {
  return this->is_begin;
}

void Command::setIsBegin(bool isBeginNew) {
  is_begin = isBeginNew;
}

void Command::setIsEnd(bool isEndNew) {
  is_end = isEndNew;
}

std::string Command::toString() const {
  std::ostringstream stringStream;
  stringStream << "Command {\n";
  stringStream << "          executable: " << this->executable << "\n";
  stringStream << "          is_begin: " << this->is_begin << "\n";
  stringStream << "          is_in_middle: " << this->is_in_middle() << "\n";
  stringStream << "          is_end: " << this->is_end << "\n";
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

  return stringStream.str();  // creates a copy
}
