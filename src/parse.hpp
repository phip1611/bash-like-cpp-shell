#pragma once

/*
 * These functions provide a BASIC set of input verifying.
 * They are not bullet-proof! The only reason for them is to
 * make sure the most fatal errors won't happen during command
 * parsing.
 */

#include <iostream>
#include <regex>

#include "properties.hpp"

/**
 * Regex that checks if something is a valid command for a shell.
 * Note that this is HIGHLY coarse-grained and not bullet-proof!
 */
extern std::regex COMMAND_CHAIN_VERIFY_REGEX;

/**
 * Checks if input is a cd input/action. This function only provides
 * a BASIC level of input verifying and is DEFINITELY not bullet-proof.
 * The main reason is to make sure the most fatal errors during actual
 * parsing won't happen.
 *
 * @param input normalized input string
 * @return input is a cd input/action
 */
bool verify_is_cd_input(std::string const * const input);

/**
 * Checks if input is a command input/action.
 * This means a single command or a chain of piped commands
 * including I/O redirection and "put in background".
 * This function only provides
 * a BASIC level of input verifying and is DEFINITELY not bullet-proof.
 * The main reason is to make sure the most fatal errors during actual
 * parsing won't happen.
 *
 * @param input normalized input string
 * @return input is a command input/action
 */
bool verify_is_command_input(std::string const * const input);

/**
 * Checks if input is a get alias input/action. This function only provides
 * a BASIC level of input verifying and is DEFINITELY not bullet-proof.
 * The main reason is to make sure the most fatal errors during actual
 * parsing won't happen.
 *
 * @param input normalized input string
 * @return input is a get alias input/action
 */
bool verify_is_get_alias_input(std::string const * const input);

/**
 * Checks if input is a set alias input/action. This function only provides
 * a BASIC level of input verifying and is DEFINITELY not bullet-proof.
 * The main reason is to make sure the most fatal errors during actual
 * parsing won't happen.
 *
 * @param input normalized input string
 * @return input is a set alias input/action
 */
bool verify_is_set_alias_input(std::string const * const input);

/**
 * Checks if input is a un alias input/action. This function only provides
 * a BASIC level of input verifying and is DEFINITELY not bullet-proof.
 * The main reason is to make sure the most fatal errors during actual
 * parsing won't happen.
 *
 * @param input normalized input string
 * @return input is a un alias input/action
 */
bool verify_is_un_alias_input(std::string const * const input);

/**
 * Parses a normalized input into the corresponding, structured data that
 * is needed for simple execution.
 *
 * @param normalized_input
 * @return
 */
ParsedInputData parse(std::string const * const normalized_input);
