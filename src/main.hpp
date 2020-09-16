/*
 * Copyright 2020 - Philipp Schuster.
 *
 * This file/project is licensed under a MIT license.
 * You can find the LICENSE file in the repository.
 */

#pragma once

#include <iostream>
#include "properties.hpp"

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

/**
 * Calls the action handler for the desired action.
 * @param data
 */
void do_shell_action(ParsedInputData & data);
