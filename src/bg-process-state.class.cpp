/*
 * Copyright 2020 - Philipp Schuster.
 *
 * This file/project is licensed under a MIT license.
 * You can find the LICENSE file in the repository.
 */

// Background Processes class.

#include "bg-process-state.class.hpp"

// constructor with pid
BgProcessState::BgProcessState(pid_t pid_new) : pid(pid_new) {}

void BgProcessState::set_done() {
  this->done = true;
}

bool BgProcessState::isDone() const {
  return done;
}

pid_t BgProcessState::getPid() const {
  return pid;
}
