// C++ Includes
#include <iostream>
#include <csignal> // c signal.h

// C includes
#include <readline/history.h>
#include <readline/readline.h>

// Own includes
#include "main.hpp"
#include "strings.hpp"

static void sig_handler(int sig) {
    if (sig == SIGINT) {
        // Interrupt from keyboard; Ctrl+C
        // don't stop our shell with an error (default behaviour)
        // TODO I don't know why this check is necessary, because SIGINT stands already in signal() function call..
        printf("\n"); // Move to a new line
        rl_on_new_line(); // Regenerate the prompt on a newline
        rl_replace_line("", 0); // Clear the previous text
        rl_redisplay();
    }
}


int main() {
    // Interrupt from keyboard; Ctrl+C
    signal(SIGINT, sig_handler);

    // Configure readline to auto-complete paths when the tab key is hit.
    rl_bind_key('\t', rl_complete); // auto completes paths (from current pwd)

    while(true) {
        std::string input = get_input();

        // Add input to history.
        add_history(input.c_str());

        //std::cout << "Input is: '" << input_str << "'" << std::endl;
    }

    readline_cleanup();
	return 0;
}

static void readline_cleanup() {
    // readline cleanup
    // there will be 200k~ still reachable.. probably by design?
    // but no really "leak"
    // https://stackoverflow.com/questions/55196451/gnu-readline-enormous-memory-leak
    clear_history();
    rl_clear_history(); // also frees some private data
    rl_clear_signals();
    rl_clear_pending_input();
    rl_clear_message();
    rl_clear_visible_line();
}

static std::string get_input() {
    char * input = readline("$ ");

    if (input == nullptr) {
        // this happens e.g. when CTRL+D is pressed

        printf("\n"); // Move to a new line
        std::cout << "shell session terminated" << std::endl;
        readline_cleanup();
        exit(0);
    }

    // creates a deep copy; string has a constructor for char *
    std::string input_str = normalize_input(input);
    free(input);
    return input_str;
}
