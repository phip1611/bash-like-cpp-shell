/*
 * Copyright 2020 - Philipp Schuster.
 *
 * This file/project is licensed under a MIT license.
 * You can find the LICENSE file in the repository.
 */

// functions that handles the actual action that the user wants to do
// (after parsing is done)

#pragma once

#include "parsed-input-data.class.hpp"

const unsigned PIPE_READ = 0;
const unsigned PIPE_WRITE = 1;

/**
 * Performs a 'cd' action.
 *
 * @param data parsed input data
 */
void action_cd(ParsedInputData * data);

/**
 * Performs a command chain action. This means
 * one or multiple (piped) commands including
 * I/O redirection, passing arguments, etc.
 *
 * @param data parsed input data
 */
void action_command(ParsedInputData * data);

/**
 * Performs an alias action, like storing a new alias.
 *
 * @param data parsed input data
 */
void action_alias(ParsedInputData * data, InputKind aliasKind);
