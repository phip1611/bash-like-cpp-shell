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
 * Interprets the input as normalized string of type "cd input" and
 * extracts all relevant information.
 *
 * @param input
 * @return
 */
std::string parse_cd_data(std::string const * const input);

/**
 * Parsed a complete command string with piped commands and I/O redirection.
 * @param input
 * @return
 */
CommandChain parse_command_data(std::string const * const input);

/**
 * Parses a basic command. A command consists of the actual command/executable,
 * the args and I/O redirection. The input string must be trimmed and normalized!
 * @param input
 * @return
 */
Command parse_basic_command_data(std::string const * const input, CommandPosition pos);

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

/**
 * Finds the path of the executable that shall be executed. This is either directly provided
 * (e.g. "./my_bin" or "/usr/bin/cat") or searched in $PATH. If no binary can found an
 * empty optional is returned.
 *
 * @param command
 * @return Path to executable.
 */
std::optional<std::string> get_executable_path(std::string * command);

/**
 * Parses the args for a command.
 *
 * @param basic_command_string_parts
 * @return args vector
 */
std::vector<std::string> parse_basic_command_args(std::vector<std::string> & basic_command_string_parts);
