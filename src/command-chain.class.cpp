/*
 * Copyright 2020 - Philipp Schuster.
 *
 * This file/project is licensed under a MIT license.
 * You can find the LICENSE file in the repository.
 */

#include <string>
#include <sstream>
#include "command-chain.class.hpp"

std::string CommandChain::toString() {
    std::ostringstream stringStream;
    stringStream << "CommandChain {\n";
    stringStream << "      background: " << this->background << "\n";
    stringStream << "      basic_commands:\n";
    for (unsigned i = 0; i < this->basic_commands.size(); i++) {
        stringStream << "        [" << i << "]" << this->basic_commands[i].toString() << "\n";
    }
    stringStream << "    }";

    return stringStream.str(); // creates a copy
}

const std::vector<Command> &CommandChain::getBasicCommands() const {
    return basic_commands;
}

void CommandChain::setBasicCommands(const std::vector<Command> &basicCommands) {
    basic_commands = basicCommands;
}

bool CommandChain::isBackground() const {
    return background;
}

void CommandChain::setBackground(bool backgroundNew) {
    CommandChain::background = backgroundNew;
}

size_t CommandChain::size() {
    return this->getBasicCommands().size();
}
