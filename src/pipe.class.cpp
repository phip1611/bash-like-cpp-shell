/*
 * Copyright 2020 - Philipp Schuster.
 *
 * This file/project is licensed under a MIT license.
 * You can find the LICENSE file in the repository.
 */

// Pipe class.

#include <iostream>
#include <sstream>
#include <cstring>
#include <cassert>
#include <unistd.h>

#include "pipe.class.hpp"
#include "pipe-end.enum.hpp"

Pipe::Pipe() {
    // create a pipe
    int res = pipe(this->fds);
    if (res == -1) {
        std::cerr << "pipe() failed with error: " << strerror(errno) << std::endl;
        exit(errno);
    }
}

void Pipe::as_write_end() {
    if (this->locked) {
        std::cerr << "Can't close " << pipe_end::to_string(PipeEnd::READ)
                  << " end of pipe because the pipe is already locked! "
                  << "Should only be called ONCE per Pipe!"
                  << std::endl;
        return;
    }
    this->locked = true;
    this->close_pipe_end(PipeEnd::READ);
    this->connect_pipe_end(PipeEnd::WRITE, STDOUT_FILENO);
}

void Pipe::as_read_end() {
    if (this->locked) {
        std::cerr << "Can't close " << pipe_end::to_string(PipeEnd::WRITE)
                  << " end of pipe because the pipe is already locked!" << std::endl;
        return;
    }
    this->locked = true;
    this->close_pipe_end(PipeEnd::WRITE);
    this->connect_pipe_end(PipeEnd::READ, STDIN_FILENO);
}

void Pipe::close_pipe_end(PipeEnd pipeEnd) const {
    int res = close(this->fds[pipeEnd]);
    if (res == -1) {
        std::cerr << "Can't close " << pipe_end::to_string(pipeEnd)
                  << "(" << this->fds[pipeEnd] <<") end of pipe because " << strerror(errno) << "!" << std::endl;
    }
}

void Pipe::close_all() const {
    this->close_pipe_end(PipeEnd::READ);
    this->close_pipe_end(PipeEnd::WRITE);
}

std::string Pipe::toString() const {
    std::ostringstream stringStream;
    stringStream << "Pipe {\n";
    stringStream << "  fd[READ]: " << this->fds[PipeEnd::READ] << ",\n";
    stringStream << "  fd[WRITE]: " << this->fds[PipeEnd::WRITE] << ",\n";
    stringStream << "  locked: " << this->locked << ",\n";
    stringStream << "}";

    return stringStream.str(); // creates a copy
}

void Pipe::connect_pipe_end(PipeEnd pipeEnd, int file_no) const {
    assert(file_no == STDIN_FILENO || file_no == STDOUT_FILENO);

    // duplicates STDIN into fds[READ_END] or
    // STDOUT into fds[WRITE_END]
    int res = dup2(this->fds[pipeEnd], file_no);
    if (res == -1) {
        std::cerr << "Can't connect "
                  << pipe_end::to_string(pipeEnd)
                  <<  "-end of pipe with "
                  << (file_no == STDIN_FILENO ? "STDIN" : "STDOUT")
                  << ": "
                  << strerror(errno) << std::endl;
    }
}
