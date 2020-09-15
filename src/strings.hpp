#pragma once

#include <iostream>
#include <regex>

/**
 * Reads a c-string and creates an C++ string. Removes all spaces at the begin
 * and the end, and replaces all double (or more) spaces with single spaces.
 *
 * @return normalized string or ""
 */
std::string normalize_input(char const * const);

bool str_starts_with(std::string const * const, std::string const * const);

/**
 * Tests if the substring inside the string contains no spaces aka only a "real world".
 * @param from from index (inclusive)
 * @param to to index (exclusive)
 * @return if the substring inside the string contains no spaces aka only a "real world".
 */
bool str_contains_single_word_from_to(std::string const *const input, unsigned from, unsigned to);

bool str_matches_regex(std::string const * const, std::regex const * const);

