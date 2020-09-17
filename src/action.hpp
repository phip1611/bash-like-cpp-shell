/*
 * Copyright 2020 - Philipp Schuster.
 *
 * This file/project is licensed under a MIT license.
 * You can find the LICENSE file in the repository.
 */

#pragma once

// concrete actions, like changing the pwd, executing a command or modify aliases

#include "parsed-input-data.class.hpp"

const unsigned PIPE_READ = 0;
const unsigned PIPE_WRITE = 1;

/**
 * Performs a cd action.
 * @param data parsed input data
 */
void action_cd(ParsedInputData * data);

/**
 * Performs a command action.
 * @param data parsed input data
 */
void action_command(ParsedInputData * data);

/**
 * Performs an alias action.
 * @param data parsed input data
 */
void action_alias(ParsedInputData * data, InputKind aliasKind);
