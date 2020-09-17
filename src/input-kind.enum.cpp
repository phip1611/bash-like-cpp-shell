/*
 * Copyright 2020 - Philipp Schuster.
 *
 * This file/project is licensed under a MIT license.
 * You can find the LICENSE file in the repository.
 */

// Input Kind enum.

#include "input-kind.enum.hpp"

std::string input_kind::to_string(InputKind const ik) {
    switch (ik) {
        case EMPTY:
            return "EMPTY";
        case CD:
            return "CD";
        case EXIT:
            return "EXIT";
        case COMMAND:
            return "COMMAND";
        case SET_ALIAS:
            return "SET_ALIAS";
        case GET_ALIAS:
            return "GET_ALIAS";
        case UN_ALIAS:
            return "UN_ALIAS";
        case UNKNOWN:
        default:
            return "UNKNOWN";
    }
}
