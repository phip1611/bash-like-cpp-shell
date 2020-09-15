#include <cassert>
#include <sstream>
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
    stringStream << "  type: " << input_kind_to_string(this->type) << "\n";

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

std::string input_kind_to_string(InputKind const ik) {
    switch (ik) {
        case EMPTY:
            return "EMPTY";
        case CD:
            return "CD";
        case EXIT:
            return "EXIT";
        case COMMAND:
            return "COMMAND";
        case SET_ALIAS:
            return "SET_ALIAS";
        case GET_ALIAS:
            return "GET_ALIAS";
        case UN_ALIAS:
            return "UN_ALIAS";
        case UNKNOWN:
        default:
            return "UNKNOWN";
    }
}

std::string command_position_to_string(CommandPosition const cp) {
    switch (cp) {
        case BEGIN:
            return "BEGIN";
        case END:
            return "END";
        case IN_THE_MIDDLE:
        default:
            return "IN_THE_MIDDLE";
    }
}

const std::string &Command::getCommand() const {
    return command;
}

const std::vector<std::string> &Command::getArgs() const {
    return args;
}

const std::string &Command::getAbsExecutablePath() const {
    return abs_executable_path;
}

const std::optional<std::string> &Command::getInputRedFile() const {
    return input_red_file;
}

const std::optional<std::string> &Command::getOutputRedFile() const {
    return output_red_file;
}

void Command::setCommand(const std::string &commandNew) {
    Command::command = commandNew;
}

void Command::setArgs(const std::vector<std::string> &argsNew) {
    Command::args = argsNew;
}

void Command::setAbsExecutablePath(const std::string &absExecutablePathNew) {
    abs_executable_path = absExecutablePathNew;
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

std::string Command::toString() {
    std::ostringstream stringStream;
    stringStream << "Command {\n";
    stringStream << "          command: " << this->command << "\n";
    stringStream << "          abs_executable_path: " << this->abs_executable_path << "\n";
    stringStream << "          position: " << command_position_to_string(this->position) << "\n";
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
