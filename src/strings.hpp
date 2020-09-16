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
bool str_contains_single_word_from_to(std::string const *const, unsigned from, unsigned to);

/**
 * Checks if string only contains given chars in given range.
 * @param input
 * @param from from index (inclusive)
 * @param to to index (exclusive)
 * @param chars
 * @return if string only contains given chars in given range
 */
bool str_contains_only_given_chars(std::string const *const input, unsigned from, unsigned to, std::string const * const chars);

/**
 * Splits a string into sub strings by a string delimiter.
 * @param str
 * @param delim
 * @return
 */
std::vector<std::string> str_split_str(const std::string * str, const std::string& delim);

/**
 * Splits a string into sub strings by a character delimiter.
 * @param str
 * @param delim
 * @return
 */
std::vector<std::string> str_split_char(const std::string * str, char const delim);

/**
 * Trims a string at the begin and at the end.
 * @param str
 * @return
 */
void trim(std::string &s);

// trim from start (in place)
void ltrim(std::string &s);

// trim from end (in place)
void rtrim(std::string &s);
