#pragma once
#ifndef USERINPUT_HPP
#define USERINPUT_HPP

std::string trim(const std::string& str);

class UserInput {
public:
    static int getIntInRange(int min, int max, const std::string& prompt);
    static char getChar(const std::string& prompt, const std::string& validChars);
    static std::string getLine(const std::string& prompt);
    // Potentially other helpers, e.g., to get yes/no confirmation
};
#endif
