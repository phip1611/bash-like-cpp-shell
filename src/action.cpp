/*
 * Copyright 2020 - Philipp Schuster.
 *
 * This file/project is licensed under a MIT license.
 * You can find the LICENSE file in the repository.
 */

// functions that handles the actual action that the user wants to do
// (after parsing is done)

#include <zconf.h>
#include <cstring>
#include <sys/wait.h>

#include "action.hpp"

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
    int pipe_fd[2]; // the pipe fds that are created per iteration
    pid_t pid;
    std::optional<int> fd_in = std::nullopt;

    // if we have an I/O redirect on the first file: open the file and get the file descriptor!
    if (data->getDataCommandChain().getBasicCommands()[0].getInputRedFile().has_value()) {
        FILE *ir = fopen(data->getDataCommandChain().getBasicCommands()[0].getInputRedFile()->c_str(), "r");
        fd_in.emplace(fileno(ir));
        // TODO close ir?
    }

    for (unsigned i = 0; i < data->getDataCommandChain().size(); i++) {
        Command const &curr_cmd = data->getDataCommandChain().getBasicCommands()[i];
        bool has_next = i + 1 != data->getDataCommandChain().size();
        if (has_next) {
            // we create pipe before it is transferred into both address spaces (via fork())
            int res = pipe(pipe_fd);
            if (res == -1) {
                fprintf(stderr, "Error creating pipe! %s\n", strerror(errno));
            }
        }

        pid = fork();
        if (pid < 0) {
            fprintf(stderr, "failure during fork!\n");
            exit(errno);
        }
        pids.push_back(pid);

        // child: this code is responsible for connecting it's stdin and stdout with the proper fd's from
        // the pipes;
        if (pid == 0) {
            // the child process never uses the read end of the just created pipe; it is for the next child
            if (has_next) close(pipe_fd[PIPE_READ]);

            // If we have no value here then it's the first command in the chain. It just reads from stdin.
            // If we have a value here in the first command then because it's an input redirect ('cat < file.txt')
            // If we have a value here in a non-first command then this means:
            // we want to connect the output from the previous process with stdin of the current one
            if (fd_in.has_value()) dup2(fd_in.value(), STDIN_FILENO);

            // Output redirection
            if (has_next) {
                // We connect stdout of this process with the write end of the pipe
                dup2(pipe_fd[PIPE_WRITE], STDOUT_FILENO);
            } else if (curr_cmd.getOutputRedFile().has_value()) {
                // else we connect stdout with the descriptor of the file
                FILE *of = fopen(curr_cmd.getOutputRedFile().value().c_str(), "w");
                dup2(fileno(of), STDOUT_FILENO);
                // TODO close of?
            }

            execv(curr_cmd.getExecutablePath().c_str(), curr_cmd.build_argv());
            fprintf(stderr, "Exec '%s' failed!\n", curr_cmd.getExecutablePath().c_str());
            exit(errno);
        }
        // parent
        else {
            // Close the reading end of the pipe that was created in the previous iteration step
            // this is really important, otherwise the whole application (chain) could stuck when
            // the internal 64KB buffer (Linux) is full, e.g. when 'cat < in_65kb.txt | grep -i hi'
            if (fd_in.has_value()) close(fd_in.value());

            // if a pipe has just been created
            if (has_next) {
                close(pipe_fd[PIPE_WRITE]);
                // we set the reading end of the just created pipe to fd_in in order for the
                // next child process, that stdin can be connected with this pipe end
                fd_in.emplace(pipe_fd[PIPE_READ]);
            }
        }
    }

    // TODO also add async wait
    if (!data->getDataCommandChain().isBackground()) {
        for (unsigned i = 0; i < data->getDataCommandChain().size(); i++) {
            int res = waitpid(pids[i], &pid_states[i], 0);
            // actually we do not need to output the pid_states here; just return
            if (res == -1) {
                fprintf(stderr, "Error waiting for child by pid! %s\n", strerror(errno));
            }
        }
    }
}

/**
 * Performs an alias action, like storing a new alias.
 *
 * @param data parsed input data
 */
void action_alias(ParsedInputData *data, InputKind aliasKind) {
    // TODO
}
