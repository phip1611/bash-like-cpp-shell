/*
 * Copyright 2020 - Philipp Schuster.
 *
 * This file/project is licensed under a MIT license.
 * You can find the LICENSE file in the repository.
 */

// Pipe class.

#include <zconf.h>
#include <iostream>
#include <sstream>

#include "pipe.class.hpp"
#include "pipe-end.enum.hpp"

Pipe::Pipe() {
    // create a pipe
    pipe(this->fds);
}

void Pipe::as_write_end() {
    if (this->read_end_closed) {
        std::cerr << "Can't close " << pipe_end::to_string(PipeEnd::READ)
                  << " end of pipe because the pipe is already locked!" << std::endl;
        return;
    }
    this->close_pipe_end(PipeEnd::READ);
    this->read_end_closed = true;

    // Makes write end fd a copy of STDOUT_FILENO
    // in other words: connects stdout with write end of pipe
    int res = dup2(this->fds[PipeEnd::WRITE], STDOUT_FILENO);
    if (res == -1) {
        std::cerr << "Can't connect write end of pipe with stdout: " << strerror(errno) << std::endl;
    }
}

void Pipe::as_read_end() {
    if (this->write_end_closed) {
        std::cerr << "Can't close " << pipe_end::to_string(PipeEnd::WRITE)
                  << " end of pipe because the pipe is already locked!" << std::endl;
        return;
    }
    this->close_pipe_end(PipeEnd::WRITE);
    this->write_end_closed = true;

    // Makes read end fd a copy of STDIN_FILENO
    // in other words: connects stdin with read end of pipe
    int res = dup2(this->fds[PipeEnd::READ], STDIN_FILENO);
    if (res == -1) {
        std::cerr << "Can't connect read end of pipe with stdin: " << strerror(errno) << std::endl;
    }
}

void Pipe::close_pipe_end(PipeEnd pipeEnd) {
    int res = close(this->fds[pipeEnd]);
    if (res == -1) {
        std::cerr << "Can't close " << pipe_end::to_string(pipeEnd)
                  << "(" << this->fds[pipeEnd] <<") end of pipe because " << strerror(errno) << "!" << std::endl;
    }
}

// TODO do in Destructor?!
void Pipe::close_all() const {
    int res = close(this->fds[PipeEnd::READ]);
    if (res == -1) {
        std::cerr << "Can't close " << pipe_end::to_string(PipeEnd::READ)
                  << " end of pipe because " << strerror(errno) << "!" << std::endl;
    }
    res = close(this->fds[PipeEnd::WRITE]);
    if (res == -1) {
        std::cerr << "Can't close " << pipe_end::to_string(PipeEnd::WRITE)
                  << " end of pipe because " << strerror(errno) << "!" << std::endl;
    }
}

std::string Pipe::toString() const {
    std::ostringstream stringStream;
    stringStream << "Pipe {\n";
    stringStream << "  fd[READ]: " << this->fds[PipeEnd::READ] << ",\n";
    stringStream << "  fd[WRITE]: " << this->fds[PipeEnd::WRITE] << ",\n";
    stringStream << "  read_end_closed: " << this->read_end_closed << ",\n";
    stringStream << "  write_end_closed: " << this->write_end_closed << ",\n";
    stringStream << "}";

    return stringStream.str(); // creates a copy
}
