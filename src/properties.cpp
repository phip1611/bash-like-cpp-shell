/*
 * Copyright 2020 - Philipp Schuster.
 *
 * This file/project is licensed under a MIT license.
 * You can find the LICENSE file in the repository.
 */

#include <cassert>
#include <sstream>
#include <memory.h>
#include "properties.hpp"


InputKind ParsedInputData::getType() const {
    return type;
}

void ParsedInputData::setType(InputKind new_type) {
    ParsedInputData::type = new_type;
}

std::string &ParsedInputData::getDataCdDir() {
    assert(this->type == InputKind::CD);
    assert(this->dataCdDir.has_value());
    return this->dataCdDir.value();
}

CommandChain &ParsedInputData::getDataCommandChain() {
    assert(this->type == InputKind::COMMAND);
    assert(this->dataCommandChain.has_value());
    return this->dataCommandChain.value();
}

std::string &ParsedInputData::getDataAliasName() {
    assert(this->type == InputKind::GET_ALIAS || this->type == InputKind::UN_ALIAS);
    assert(this->dataAliasName.has_value());
    return this->dataAliasName.value();
}

std::string &ParsedInputData::getDataAliasValue() {
    assert(this->type == InputKind::SET_ALIAS);
    assert(this->dataAliasValue.has_value());
    return this->dataAliasValue.value();
}

std::string ParsedInputData::toString() {
    std::ostringstream stringStream;
    stringStream << "ParsedInputData {\n";
    stringStream << "  type: " << input_kind::to_string(this->type) << "\n";

    stringStream << "  dataCdDir: ";
    if (this->dataCdDir.has_value()) {
        stringStream << this->dataCdDir.value() << "\n";
    } else {
        stringStream << "<none>\n";
    }

    stringStream << "  dataCommandChain: ";
    if (this->dataCommandChain.has_value()) {
        stringStream << this->dataCommandChain->toString() << "\n";
    } else {
        stringStream << "<none>\n";
    }


    stringStream << "  dataAliasName: ";
    if (this->dataAliasName.has_value()) {
        stringStream << this->dataAliasName.value() << "\n";
    } else {
        stringStream << "<none>\n";
    }

    stringStream << "  dataAliasValue: ";
    if (this->dataAliasValue.has_value()) {
        stringStream << this->dataAliasValue.value() << "\n";
    } else {
        stringStream << "<none>\n";
    }

    stringStream << "}";

    return stringStream.str(); // creates a copy
}

void ParsedInputData::setDataCdDir(const std::optional<std::string> dataCdDirNew) {
    ParsedInputData::dataCdDir = dataCdDirNew;
}

void ParsedInputData::setDataCommandChain(const std::optional<CommandChain> dataCommandChainNew) {
    ParsedInputData::dataCommandChain = dataCommandChainNew;
}

void ParsedInputData::setDataAliasName(const std::optional<std::string> dataAliasNameNew) {
    ParsedInputData::dataAliasName = dataAliasNameNew;
}

void ParsedInputData::setDataAliasValue(const std::optional<std::string> dataAliasValueNew) {
    ParsedInputData::dataAliasValue = dataAliasValueNew;
}

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


