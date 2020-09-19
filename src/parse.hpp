/*
 * Copyright 2020 - Philipp Schuster.
 *
 * This file/project is licensed under a MIT license.
 * You can find the LICENSE file in the repository.
 */

#pragma once

/*
 * These functions provide a BASIC set of input verifying.
 * They are not bullet-proof! The only reason for them is to
 * make sure the most fatal errors won't happen during executable
 * parsing.
 */

// All functions related to verifying and parsing the input.

#include <iostream>
#include <regex>

#include "parsed-input-data.class.hpp"

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
 * This function only provides a BASIC level of input verifying and
 * is DEFINITELY not bullet-proof. The main reason is to make sure
 * the most fatal errors during actual parsing won't happen
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
 * Interprets the input as normalized string of type "cd input" and
 * extracts all relevant information.
 *
 * @param input
 * @return
 */
std::string parse_cd_data(std::string const * const input);

/**
 * Parsed a complete command chain string with piped commands and I/O redirection.
 * @param input
 * @return
 */
CommandChain parse_command_chain(std::string const * const input);

/**
 * Parses a basic command. A command consists of the actual command/executable,
 * the args and I/O redirection. The input string must be trimmed and normalized!
 * @param input
 * @return
 */
Command parse_command_chain_command(std::string const * const input, CommandPosition pos);

/**
 * Helper function for parse_command_chain_command(). Enriches the command with data for
 * either the input redirect or the output redirect.
 * This changes/modifies the command object.
 * @param cmd
 * @param basic_command_str
 */
void parse_command_chain_command_io_redirection(Command & cmd, std::string const * const basic_command_str);

/**
 * Parses the args for a command.
 * This doesn't change the command object.
 *
 * @param basic_command_string_parts
 * @return args vector
 */
std::vector<std::string> parse_command_chain_command_args(std::vector<std::string> & basic_command_string_parts);

/**
 * Checks if the specified executable exists and is executable either in $PATH or in the file system.
 * (e.g. "./my_bin" or "/usr/bin/cat") or searched in $PATH.
 *
 * @param command
 * @return file exists and is executable
 */
bool check_executable_path_exists(std::string * command);
