/*
 * Copyright 2020 - Philipp Schuster.
 *
 * This file/project is licensed under a MIT license.
 * You can find the LICENSE file in the repository.
 */

// All functions related to aliases. Store, Get, Delete..

#pragma once

#include <string>

const std::string GET_ALIAS_COMMAND_PREFIX = "getalias";
const std::string SET_ALIAS_COMMAND_PREFIX = "alias";
const std::string UN_ALIAS_COMMAND_PREFIX = "unalias";

const std::string GET_ALIAS_NAME_ALLOWED_CHARS =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_";
const std::string SET_ALIAS_VALUE_ALLOWED_CHARS =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_- ";
