/*
 * Copyright 2020 - Philipp Schuster.
 *
 * This file/project is licensed under a MIT license.
 * You can find the LICENSE file in the repository.
 */

// Background Process State class.

#pragma once

#include <sys/wait.h>

class BgProcessState {
 private:
  bool done = false;
  pid_t pid;

 public:
  BgProcessState(pid_t pid);
  void set_done();

  bool isDone() const;

  pid_t getPid() const;
};
