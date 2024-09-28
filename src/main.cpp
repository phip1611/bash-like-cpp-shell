/*
 * Copyright 2020 - Philipp Schuster.
 *
 * This file/project is licensed under a MIT license.
 * You can find the LICENSE file in the repository.
 */

// Main / phipsshell

// C++ Includes
#include <csignal>  // c signal.h
#include <iostream>

// C includes
#include <readline/history.h>
#include <readline/readline.h>

// Own includes
#include "action.hpp"
#include "bg-processes.hpp"
#include "main.hpp"
#include "parse.hpp"
#include "parsed-input-data.class.hpp"
#include "strings.hpp"

int main() {
  // Interrupt from keyboard; Ctrl+C
  signal(SIGINT, sig_handler);

  // Configure readline to auto-complete paths when the tab key is hit.
  rl_bind_key('\t', rl_complete);  // auto completes paths (from current pwd)

  while (true) {
    // we check for finished background processes after each iteration
    // bach handles it in the same/similar way
    check_bg_processes();

    // get user input (user sees prompt here)
    std::string input = get_input();

    ParsedInputData parsedInputData = parse(&input);

    // DEBUG
    if (parsedInputData.getType() == InputKind::UNKNOWN) {
      std::cerr << "Unknown/illegal command!" << std::endl;
    }
    // std::cout << parsedInputData.toString() << std::endl;

    // all actions that don't "survive the whole loop"
    if (parsedInputData.getType() == InputKind::EXIT)
      break;
    if (parsedInputData.getType() == InputKind::UNKNOWN ||
        parsedInputData.getType() == InputKind::EMPTY)
      continue;  // ask again for input

    do_shell_action(parsedInputData);

    // Add input to history; only store real commands or alias; no exit or
    add_history(input.c_str());

    // std::cout << "Input is: '" << input_str << "'" << std::endl;
  }

  readline_cleanup();
  return 0;
}

void do_shell_action(ParsedInputData& data) {
  if (data.getType() == InputKind::CD) {
    action_cd(&data);
  } else if (data.getType() == InputKind::COMMAND) {
    action_command(&data);
  } else if (data.getType() == InputKind::GET_ALIAS) {
    action_alias(&data, InputKind::GET_ALIAS);
  } else if (data.getType() == InputKind::SET_ALIAS) {
    action_alias(&data, InputKind::SET_ALIAS);
  } else if (data.getType() == InputKind::UN_ALIAS) {
    action_alias(&data, InputKind::UN_ALIAS);
  }
}

static void readline_cleanup() {
  // readline cleanup
  // there will be 200k~ still reachable.. probably by design?
  // but no really "leak"
  // https://stackoverflow.com/questions/55196451/gnu-readline-enormous-memory-leak
  clear_history();
  rl_clear_history();  // also frees some private data
  rl_clear_signals();
  rl_clear_pending_input();
  rl_clear_message();
  rl_clear_visible_line();
}

static std::string get_input() {
  char* input = readline("$ ");

  if (input == nullptr) {
    // this happens e.g. when CTRL+D is pressed

    printf("\n");  // Move to a new line
    std::cout << "shell session terminated" << std::endl;
    readline_cleanup();
    exit(0);
  }

  // creates a deep copy; string has a constructor for char *
  std::string input_str = normalize_input(input);
  free(input);
  return input_str;
}

static void sig_handler(int sig) {
  if (sig == SIGINT) {
    // Interrupt from keyboard; Ctrl+C
    // don't stop our shell with an error (default behaviour)
    // TODO I don't know why this check is necessary, because SIGINT stands
    // already in signal() function call..
    printf("\n");            // Move to a new line
    rl_on_new_line();        // Regenerate the prompt on a newline
    rl_replace_line("", 0);  // Clear the previous text
    rl_redisplay();
  }
}

void check_bg_processes() {
  for (auto& p : bg_processes) {
    // TODO
    // remove old entries; otherwise we use infinite memory over time
    if (p->isDone())
      continue;

    // waitpid WNOHANG does the magic here :)
    int status_code[1];
    // status code IS NOT exit code!
    // see https://linux.die.net/man/2/waitpid
    pid_t res = waitpid(p->getPid(), status_code, WNOHANG);
    // returns the pid on sucess
    if (res != 0) {
      printf("-- BG-Process with PID %d finished with Status Code %d\n",
             p->getPid(), status_code[0]);
      p->set_done();
    }
  }
}
