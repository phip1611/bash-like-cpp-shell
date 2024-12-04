/*
 * Copyright 2020 - Philipp Schuster.
 *
 * This file/project is licensed under a MIT license.
 * You can find the LICENSE file in the repository.
 */

// Command class.

#include <string>
#include <vector>

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
   * Arguments for the command.
   */
  std::vector<std::string> args = {};
  /**
   * If the command is the first in the chain.
   */
  bool is_begin = false;
  /**
   * If the command is the last in the chain.
   */
  bool is_end = false;
  /**
   * If present, the name of the input redirect file.
   */
  std::optional<std::string> input_red_file = std::nullopt;
  /**
   * If present, the name of the output redirect file.
   */
  std::optional<std::string> output_red_file = std::nullopt;

 public:
  const std::string& getExecutable() const;

  const std::vector<std::string>& getArgs() const;

  const std::optional<std::string>& getInputRedFile() const;

  const std::optional<std::string>& getOutputRedFile() const;

  void setExecutable(const std::string& executable);

  void setArgs(const std::vector<std::string>& args);

  void setInputRedFile(const std::optional<std::string>& inputRedFile);

  void setOutputRedFile(const std::optional<std::string>& outputRedFile);

  void setIsBegin(bool isBegin);

  void setIsEnd(bool isEnd);

  std::string toString() const;

  /**
   * If this->position == CommandPositionFlags::Begin
   * @return this->position == CommandPositionFlags::Begin
   */
  bool is_first() const;

  /**
   * If this->position == CommandPositionFlags::End
   * @return this->position == CommandPositionFlags::End
   */
  bool is_last() const;

  /**
   * If this->position == CommandPositionFlags::IN_THE_MIDDLE
   * @return this->position == CommandPositionFlags::IN_THE_MIDDLE
   */
  bool is_in_middle() const;

  /**
   * Builds a null terminated array with all args.
   * Allocates memory out of C++s new/delete scope.
   * @return
   */
  char** build_argv() const;
};