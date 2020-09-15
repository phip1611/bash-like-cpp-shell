#pragma once

#include <iostream>
#include <optional>

/**
 * Describes the kind of valid input.
 */
enum InputKind {
    /** Unknown and invalid inputs. Mostly this will be the case for invalid input. */
    UNKNOWN,
    /** Empty. Just display next row. */
    EMPTY,
    /** Change present working directory */
    CD,
    /** Exit with success. */
    EXIT,
    /** Single command or command chain including IO redirection and put in background. */
    COMMAND,
    /** Set's an alias that is available during runtime. */
    SET_ALIAS,
    /** Prints the value of an alias. */
    GET_ALIAS,
    /** Deletes an alias */
    UN_ALIAS,
};

std::string input_kind_to_string(InputKind);

/**
 * Data for a single command.
 */
class Command {

};

/**
 * Data for a command chain. This means a chain of commands where one programs
 * output is the next programs input (pipe). A command chain can also be put into
 * background.
 */
class CommandChain {
public:
    std::string toString();
};

class ParsedInputData {
private:
    InputKind type = InputKind::UNKNOWN;
    std::optional<std::string> dataCdDir = std::nullopt;
    std::optional<CommandChain> dataCommandChain = std::nullopt;
    std::optional<std::string> dataAliasName = std::nullopt;
    std::optional<std::string> dataAliasValue = std::nullopt;

public:
    [[nodiscard]] InputKind getType() const;

    void setType(InputKind type);

    std::string * getDataCdDir();
    CommandChain * getDataCommandChain();
    std::string * getDataAliasName();
    std::string * getDataAliasValue();

    std::string toString();
};
