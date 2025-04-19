#pragma once
#ifndef USERINPUT_HPP
#define USERINPUT_HPP

#include <string>
#include <iostream>
#include <stdexcept>

/**
 * @brief Trims whitespace characters from both ends of a string.
 *
 * @param str The string to trim.
 * @return The trimmed string.
 */
std::string trim(const std::string& str);

class UserInput {
public:
    /**
     * @brief Prompts the user for an integer input within a specified range.
     *
     * Repeatedly prompts the user until a valid integer within the range [min, max] is entered.
     * Logs errors for invalid inputs and out-of-range values.
     *
     * @param min The minimum acceptable value.
     * @param max The maximum acceptable value.
     * @param prompt The prompt to display to the user.
     * @return A valid integer input within the specified range.
     */
    static int getIntInRange(int min, int max, const std::string& prompt);

    /**
     * @brief Prompts the user for a single character input from a list of valid characters.
     *
     * Repeatedly prompts the user until a valid character is entered. Logs errors for invalid inputs.
     *
     * @param prompt The prompt to display to the user.
     * @param validChars A string of valid characters the user can input.
     * @return The valid character entered by the user.
     */
    static char getChar(const std::string& prompt, const std::string& validChars);

    /**
     * @brief Prompts the user for a line of input.
     *
     * Repeatedly prompts the user until a non-empty line is entered. The line is trimmed of whitespace.
     * Logs errors for empty or invalid inputs.
     *
     * @param prompt The prompt to display to the user.
     * @return The non-empty line of input.
     */
    static std::string getLine(const std::string& prompt);
};

#endif // USERINPUT_HPP
