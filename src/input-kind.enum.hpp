/*
 * Copyright 2020 - Philipp Schuster.
 *
 * This file/project is licensed under a MIT license.
 * You can find the LICENSE file in the repository.
 */

// Input Kind enum.

#pragma once

#include <string>

/**
 * Describes the kinds of input.
 */
enum InputKind {
  /** Unknown and invalid inputs. Mostly this will be the case for invalid
     input. */
  UNKNOWN,
  /** Empty. Just display next row. */
  EMPTY,
  /** Change present working directory */
  CD,
  /** Exit with success. */
  EXIT,
  /** Single command or command chain including IO redirection and put in
     background. */
  COMMAND,
  /** Set's an alias that is available during runtime. */
  SET_ALIAS,
  /** Prints the value of an alias. */
  GET_ALIAS,
  /** Deletes an alias */
  UN_ALIAS,
};

namespace input_kind {
/**
 * Transforms a enum value into it's string representation.
 *
 * @param ik
 * @return string representation
 */
std::string to_string(InputKind const ik);
}  // namespace input_kind
