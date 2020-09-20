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
    int fds[2] = {0, 0};
    /**
     * The main purpose of the lock is to make sure that
     * this operation is done exactly once per pipe.
     */
    bool read_end_closed = false;
    /**
     * The main purpose of the lock is to make sure that
     * this operation is done exactly once per pipe.
     */
    bool write_end_closed = false;
    void close_pipe_end(PipeEnd pipeEnd);
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
     * before the object is deleted.
     */
    // TODO do in Destructor?!
    void close_all() const;

    /**
     * Creates a string representaiton.
     */
    std::string toString() const;
};
