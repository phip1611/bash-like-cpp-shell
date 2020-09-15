#pragma once

#include <iostream>

/**
 * Get normalized input from readline.
 * Normalized means no spaces at begin and end, and only "single spaces" inside the string.
 *
 * Exits the problem if readline returns nullptr. This happens e.g. when CTRL+D is pressed.
 *
 * @return normalized input from readline
 */
static std::string get_input();

/**
 * Readline cleanup.
 */
static void readline_cleanup();

/**
 * Sighandler.
 * @param sig Signal number
 */
static void sig_handler(int sig);
