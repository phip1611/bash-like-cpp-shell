#pragma once

#include <iostream>

#include "properties.hpp"

/**
 * Checks if input is a cd input/action.
 * @param input normalized input string
 * @return input is a cd input/action
 */
bool is_cd_input(std::string const * const input);

/**
 * Checks if input is a command input/action.
 * @param input normalized input string
 * @return input is a command input/action
 */
bool is_command_input(std::string const * const input);

/**
 * Checks if input is a get alias input/action.
 * @param input normalized input string
 * @return input is a get alias input/action
 */
bool is_get_alias_input(std::string const * const input);

/**
 * Checks if input is a set alias input/action.
 * @param input normalized input string
 * @return input is a set alias input/action
 */
bool is_set_alias_input(std::string const * const input);

/**
 * Checks if input is a un alias input/action.
 * @param input normalized input string
 * @return input is a un alias input/action
 */
bool is_un_alias_input(std::string const * const input);


ParsedInputData parse(std::string const * const normalized_input);
