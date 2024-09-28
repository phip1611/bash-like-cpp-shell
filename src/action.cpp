/*
 * Copyright 2020 - Philipp Schuster.
 *
 * This file/project is licensed under a MIT license.
 * You can find the LICENSE file in the repository.
 */

// functions that handles the actual action that the user wants to do
// (after parsing is done)

#include <cstring>
#include <sys/wait.h>

#include "action.hpp"
#include "bg-processes.hpp"
#include "pipe.class.hpp"

/**
 * Performs a 'cd' action.
 *
 * @param data parsed input data
 */
void action_cd(ParsedInputData *data) {
    int res = chdir(data->getDataCdDir().c_str());
    if (res == -1) {
        std::cerr << "Failed to cd to '" << data->getDataCdDir() << "', "
                  << "error code is: '" << strerror(errno) << "'" << std::endl;
    }
}

/**
 * Performs a command chain action. This means
 * one or multiple (piped) commands including
 * I/O redirection, passing arguments, etc.
 *
 * @param data parsed input data
 */
void action_command(ParsedInputData *data) {
    std::vector<int> pids;
    std::vector<int> pid_states(data->getDataCommandChain().size());
    pid_t pid;

    // Each pipe connects two processes. Each process has
    // access to "pipe_to_current" and "pipe_to_next".
    // First one is used as READ-end while the latter one
    // is used as WRITE-end.
    //
    // _______________    _______________    _________
    // | cat foo.txt |    | grep -i abc |    | wc -l |
    // ---------------    ---------------    ---------
    //             ^        ^         ^        ^
    //       WRITE |--------|  R / W  |--------| READ
    //       END               E   E             END
    //                    (current child)
    //         -Pipe to Current-   -Pipe to Next-


    // Pipe that connects the previous forked process with
    // the current process. The first process in the chain has
    // no value here.
    std::optional<Pipe> pipe_to_current = std::nullopt;
    // Pipe that connects the current process with
    // the process that is created next after fork.
    // The last process in the chain has no value here.
    std::optional<Pipe> pipe_to_next = std::nullopt;

    for (unsigned i = 0; i < data->getDataCommandChain().size(); i++) {
        Command const &curr_cmd = data->getDataCommandChain().getBasicCommands()[i];

        // now prepare Pipe-Objects
        {
            // pipe_to_next to pipe_to_current object
            if (pipe_to_next.has_value()) {
                // for the record: currently this means that
                // a new copy of the pipe in pipe_to_next
                // is created and stored inside pipe_to_current

                // I assume that compiler optimization will
                // remove this overhead

                pipe_to_current.emplace(
                    pipe_to_next.value()
                );
                pipe_to_next.reset();
           }

            // Create new pipe for pipe_to_next
            // if (curr_cmd.is_in_middle()) {
            if (!curr_cmd.is_last()) {
                pipe_to_next.emplace(Pipe());
            } else {
                pipe_to_next.reset();
            }
        }

        pid = fork();
        if (pid < 0) {
            std::cerr << "Failed to fork(): '" << strerror(errno) << "'" << std::endl;
            exit(errno);
        }

        // parent
        if (pid > 0) {
            // save pid
            pids.push_back(pid);

            // Because the parent just creates pipes, forks itself
            // and the actual programs are executed (exec()) inside the child,
            // the parent must close all pipe ends that are yet in other processes

            // this is really important, otherwise the whole application (chain) could stuck when
            // the internal 64KB buffer (Linux) is full, e.g. when 'cat < in_65kb.txt | grep -i hi'
            // this is, because Linux thinks that a reader (the parent) exists but it never reads
            // from the buffer -> deadlock

            // Parent process closes all it's open FDs to the pipe
            if (pipe_to_current.has_value()) {
                pipe_to_current->close_all();
            }
        }

        // child: this code is responsible for connecting it's stdin and stdout with the proper fd's from
        // the pipes;
        else {
            // Everything here is now done in a separately address space (because we forked)

            // handle '<' and '>'
            // handle '<' and '>'
            {
                // handle '<'
                if (curr_cmd.is_first() && curr_cmd.getInputRedFile().has_value()) {
                    FILE *ir = fopen(curr_cmd.getInputRedFile()->c_str(), "r");
                    // TODO check for ir is null
                    dup2(fileno(ir), STDIN_FILENO);
                }
                // handle '>'
                if (curr_cmd.is_last() && curr_cmd.getOutputRedFile().has_value()) {
                    // note that append won't work here because we only use the
                    // '> out.file' functionality but not '>> out.file' which
                    // would require the O_APPEND flag!
                    FILE *of = fopen(curr_cmd.getOutputRedFile()->c_str(), "w");
                    dup2(fileno(of), STDOUT_FILENO);
                }
            }

            // closes Pipe ends that we don't need
            if (pipe_to_current.has_value()) {
                // process reads from this pipe
                pipe_to_current->as_read_end();
            }
            if (pipe_to_next.has_value()) {
                // process writes to this pipe
                pipe_to_next->as_write_end();
            }

            // does automatic resolution of the given executable
            // e.g. "cat", "ls" are searched in the path whereas
            // "./foobar" or "/bin/bash" are executed directly
            // this works because the process knows its own working dir
            execvp(curr_cmd.getExecutable().c_str(), curr_cmd.build_argv());
            fprintf(stderr, "Exec '%s' failed!\n", curr_cmd.getExecutable().c_str());
            exit(errno);
        }
    }

    // Wait for all child pids

    if (!data->getDataCommandChain().isBackground()) {
        for (unsigned i = 0; i < data->getDataCommandChain().size(); i++) {
            int res = waitpid(pids[i], &pid_states[i], 0);
            // actually we do not need to output the pid_states here; just return
            if (res == -1) {
                fprintf(stderr, "Error waiting for child by pid! %s\n", strerror(errno));
            }
        }
    } else {
        // add all pids as bg processes
        for (unsigned i = 0; i < data->getDataCommandChain().size(); i++) {
            bg_processes.push_back(
                new BgProcessState(pids[i])
            );
        }
    }
}

/**
 * Performs an alias action, like storing a new alias.
 *
 * @param data parsed input data
 */
void action_alias( [[maybe_unused]] ParsedInputData *data, [[maybe_unused]] InputKind aliasKind) {
    // TODO
}
