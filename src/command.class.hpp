/*
 * Copyright 2020 - Philipp Schuster.
 *
 * This file/project is licensed under a MIT license.
 * You can find the LICENSE file in the repository.
 */

// Command class.

#include <vector>
#include <string>

#include "command-position.enum.hpp"

/**
 * Data for a single command. A command means a executable with
 * it's args and possible I/O redirection. Examples are:
 * <li> 'cat foo.txt'
 * <li> 'cat &gt; foo.txt'
 * <li> 'cat foo.txt &lt; out.txt'
 * <li> 'ls -la'
 */
class Command {
private:
    /**
     * The part of the user input that describes the executable.
     * Could be "cat", "ls", "./mybinary" or "/usr/bin/bash".
     */
    std::string executable = "";
    /**
     * Arguments for the commamd.
     */
    std::vector<std::string> args = {};
    /**
     * The position inside the chain.
     */
    CommandPosition position = BEGIN;
    /**
     * If present, the name of the input redirect file.
     */
    std::optional<std::string> input_red_file = std::nullopt;
    /**
     * If present, the name of the output redirect file.
     */
    std::optional<std::string> output_red_file = std::nullopt;
public:
    const std::string &getExecutable() const;

    const std::vector<std::string> &getArgs() const;

    const std::optional<std::string> &getInputRedFile() const;

    const std::optional<std::string> &getOutputRedFile() const;

    CommandPosition getPosition() const;

    void setPosition(CommandPosition position);

    void setExecutable(const std::string &executable);

    void setArgs(const std::vector<std::string> &args);

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