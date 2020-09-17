/*
 * Copyright 2020 - Philipp Schuster.
 *
 * This file/project is licensed under a MIT license.
 * You can find the LICENSE file in the repository.
 */

// Command Position enum.

#include "command-position.enum.hpp"

std::string command_position::to_string(CommandPosition const cp) {
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
