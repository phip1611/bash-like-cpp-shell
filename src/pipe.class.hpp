/*
 * Copyright 2020 - Philipp Schuster.
 *
 * This file/project is licensed under a MIT license.
 * You can find the LICENSE file in the repository.
 */

// Pipe class.

#pragma once

#include "pipe-end.enum.hpp"

/**
 * Abstraction over UNIX pipe for the specific case here with
 * stdin/stdout redirection between processes. The typical flow
 * is that a Pipe is created, the program is forked and
 * that one process marks it's part of the Pipe as READ
 * while the other process marks it's part of the Pipe
 * as WRITE.
 *
 * Each Pipe object will exists per address space, because
 * we create a child process for each command to be executed.
 *
 * Each pipe connects two processes. Each process has
 * access to "pipe_to_current" and "pipe_to_next".
 * First one is used as READ-end while the latter one
 * is used as WRITE-end.
 */
/* _______________    _______________    _________
 * | cat foo.txt |    | grep -i abc |    | wc -l |
 * ---------------    ---------------    ---------
 *             ^        ^         ^        ^
 *       WRITE |--------|  R / W  |--------| READ
 *       END               E   E             END
 *                    (current child)
 *         -Pipe to Current-   -Pipe to Next-
 */
class Pipe {
 private:
  /**
   * The file descriptors returned by pipe() (libc).
   */
  int fds[2] = {0, 0};
  /**
   * The main purpose of the lock is to make sure that a Pipe
   * is exactly once marked as "write and" or "read end" in
   * it's address space. Good for debugging and finding errors.
   * There are no real scenarios where a process would try
   * to mark a Pipe multiple times.
   */
  bool locked = false;
  /**
   * Closes the specified end of the pipe in the current address space.
   *
   * @param pipeEnd
   */
  void close_pipe_end(PipeEnd pipeEnd) const;

  /**
   * Connects the pipe end with the specified file descriptor,
   * i.e. duplicates STDIN or STDOUT into the proper Pipe-end.
   *
   * @param pipeEnd
   * @param file_no STDIN_FILENO or STDOUT_FILENO
   */
  void connect_pipe_end(PipeEnd pipeEnd, int file_no) const;

 public:
  Pipe();

  /**
   * Marks the pipe as write end and connects
   * stdout with write end.
   */
  void as_write_end();
  /**
   * Marks the pipe as read end and connects
   * stdin with read end.
   */
  void as_read_end();

  /**
   * Closes all FDs. Must be called in parent process
   * before the object is deleted in order to avoid
   * deadlocks. Otherwise Linux things there are open
   * readers/writers which becomes a problem when the
   * internal buffer is full.
   */
  void close_all() const;

  /**
   * Creates a string representation.
   */
  [[nodiscard]] std::string toString() const;
};
