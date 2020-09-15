#pragma once

#include <iostream>

/**
 * Reads a c-string and creates an C++ string. Removes all spaces at the begin
 * and the end, and replaces all double (or more) spaces with single spaces.
 *
 * @return normalized string or ""
 */
std::string normalize_input(char const * const);
