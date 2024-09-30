/*
 * Copyright 2020 - Philipp Schuster.
 *
 * This file/project is licensed under a MIT license.
 * You can find the LICENSE file in the repository.
 */

// Pipe end enum.

#pragma once

#include <string>

enum PipeEnd {
  READ = 0,
  WRITE = 1,
};

namespace pipe_end {
/**
 * Transforms a enum value into it's string representation.
 *
 * @param cp
 * @return string representation
 */
std::string to_string(PipeEnd const pe);
}  // namespace pipe_end
