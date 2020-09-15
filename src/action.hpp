#pragma once

// concrete actions, like changing the pwd, executing a command or modify aliases

#include "properties.hpp"

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
