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

/**
 * Data for a single command.
 */
class Command {
private:
    /**
     * The actual command, for example "find" or "cat".
     */
    std::string command = "";
    /**
     * Arguments for the commamd.
     */
    std::vector<std::string> args = {};
    /**
     * Absolut or relative path to executable.
     */
    std::string executable_path = "";
    CommandPosition position = BEGIN;
    std::optional<std::string> input_red_file = std::nullopt;
    std::optional<std::string> output_red_file = std::nullopt;
public:
    const std::string &getCommand() const;

    const std::vector<std::string> &getArgs() const;

    const std::string &getExecutablePath() const;

    const std::optional<std::string> &getInputRedFile() const;

    const std::optional<std::string> &getOutputRedFile() const;

    CommandPosition getPosition() const;

    void setPosition(CommandPosition position);

    void setCommand(const std::string &command);

    void setArgs(const std::vector<std::string> &args);

    void setExecutablePath(const std::string &executablePathNew);

    void setInputRedFile(const std::optional<std::string> &inputRedFile);

    void setOutputRedFile(const std::optional<std::string> &outputRedFile);

    std::string toString();

    /**
     * Builds a null terminated array with all args.
     * Allocates memory out of C++s new/delete scope.
     * @return
     */
    char ** build_argv() const;
};

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
