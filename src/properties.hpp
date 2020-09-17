/*
 * Copyright 2020 - Philipp Schuster.
 *
 * This file/project is licensed under a MIT license.
 * You can find the LICENSE file in the repository.
 */

#pragma once

#include <iostream>
#include <optional>
#include <vector>
#include "input-kind.enum.hpp"
#include "command-position.enum.hpp"
#include "command.class.hpp"


/**
 * Data for a command chain. This means a chain of commands where one programs
 * output is the next programs input (pipe). A command chain can also be put into
 * background.
 */
class CommandChain {
private:
    /**
     * All commands in their order they should be piped together.
     */
    std::vector<Command> basic_commands = {};
    /**
     * Put in background or not.
     */
    bool background = false;
public:
    std::string toString();

    const std::vector<Command> &getBasicCommands() const;

    void setBasicCommands(const std::vector<Command> &basicCommands);

    bool isBackground() const;

    void setBackground(bool background);

    size_t size();
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

    std::string &getDataCdDir();
    CommandChain &getDataCommandChain();
    std::string &getDataAliasName();
    std::string &getDataAliasValue();

    void setDataCdDir(const std::optional<std::string> dataCdDir);

    void setDataCommandChain(const std::optional<CommandChain> dataCommandChain);

    void setDataAliasName(const std::optional<std::string> dataAliasName);

    void setDataAliasValue(const std::optional<std::string> dataAliasValue);

    std::string toString();
};
