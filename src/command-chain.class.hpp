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

#include "command.class.hpp"
#include "input-kind.enum.hpp"

// Command Chain class.

/**
 * Data for a command chain. This means a chain of commands where one programs
 * output is the next programs input (pipe). A command chain can also be put
 * into background. Valid examples for a command chain: <li> 'cat foo.txt' <li>
 * 'cat foo.txt | grep -i hello' <li> 'cat &lt; foo.txt | grep -i hello >
 * /dev/null'
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

  const std::vector<Command>& getBasicCommands() const;

  void setBasicCommands(const std::vector<Command>& basicCommands);

  bool isBackground() const;

  void setBackground(bool background);

  size_t size();
};
