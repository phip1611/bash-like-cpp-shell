/*
 * Copyright 2020 - Philipp Schuster.
 *
 * This file/project is licensed under a MIT license.
 * You can find the LICENSE file in the repository.
 */

// Pipe end enum.

#include <iostream>

#include "pipe-end.enum.hpp"

std::string pipe_end::to_string(const PipeEnd pe) {
  switch (pe) {
    case READ:
      return "READ";
    case WRITE:
      return "WRITE";
  }
  // here be dragons
  std::cerr << "Invalid value for 'PipeEnd'!" << std::endl;
  exit(-EINVAL);
}
