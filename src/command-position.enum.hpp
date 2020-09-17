/*
 * Copyright 2020 - Philipp Schuster.
 *
 * This file/project is licensed under a MIT license.
 * You can find the LICENSE file in the repository.
 */

// Command Position enum.

#pragma once

#include <string>

#include "input-kind.enum.hpp"

/**
 * Position of a command inside the chain/vector of commands.
 */
enum CommandPosition {
    BEGIN,
    IN_THE_MIDDLE,
    END,
};

namespace command_position {
    /**
     * Transforms a enum value into it's string representation.
     *
     * @param cp
     * @return string representation
     */
    std::string to_string(CommandPosition const cp);
}

