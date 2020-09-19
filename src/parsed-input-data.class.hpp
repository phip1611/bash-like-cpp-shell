/*
 * Copyright 2020 - Philipp Schuster.
 *
 * This file/project is licensed under a MIT license.
 * You can find the LICENSE file in the repository.
 */

// Parsed Input Data class.

#pragma once

#include <iostream>
#include <optional>
#include <vector>

#include "input-kind.enum.hpp"
#include "command-chain.class.hpp"

/**
 * Describes the parsed data for all possible input values.
 * <li> 'setalias foo=bar'
 * <li> 'ps aux'
 * <li> 'ls -la | grep -i uni'
 * <li> 'cat < in.txt | grep -i uni > /dev/null'
 * <li> 'cat < in.txt | grep -i uni > /dev/null &'
 * are all parsed into an object of this class.
 */
class ParsedInputData {
private:
    /**
     * The type of the input.
     */
    InputKind type = InputKind::UNKNOWN;
    /**
     * If present, the data for the 'cd' action.
     */
    std::optional<std::string> dataCdDir = std::nullopt;
    /**
     * If present, the data for the 'execute command chain' action.
     */
    std::optional<CommandChain> dataCommandChain = std::nullopt;
    /**
     * If present, the data for the 'alias (get-, un-)' action.
     */
    std::optional<std::string> dataAliasName = std::nullopt;
    /**
    * If present, the data for the 'alias (set-)' action.
    */
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
