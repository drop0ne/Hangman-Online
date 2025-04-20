//------------------------------------------------------------------------------
// UserInput.h
//------------------------------------------------------------------------------

#pragma once

inline std::string trim(const std::string& s) {
    size_t a = s.find_first_not_of(" \t");
    if (a == std::string::npos) return "";
    size_t b = s.find_last_not_of(" \t");
    return s.substr(a, b - a + 1);
}

class UserInput {
public:
    static int getIntInRange(int min, int max, const std::wstring& prompt);
    static wchar_t getChar(const std::wstring& prompt);
    static std::wstring getLine(const std::wstring& prompt);
};
