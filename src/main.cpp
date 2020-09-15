// C++ Includes
#include <iostream>

// C includes
#include <readline/history.h>
#include <readline/readline.h>

// Own includes
#include "lib.hpp"


int main() {
    while(true) {
        char * input = readline("$ ");
        // creates a deep copy; string has a constructor for char *
        std::string input_str = input;
        free(input);

        // std::cout << "Input is: '" << input << "'" << std::endl;


    }
	return 0;
}
