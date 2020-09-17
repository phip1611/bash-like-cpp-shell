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