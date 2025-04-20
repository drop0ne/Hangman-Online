//------------------------------------------------------------------------------
// UserInput.cpp
//------------------------------------------------------------------------------

#include "PCH.h"
#include "UserInput.h"

int UserInput::getIntInRange(int min, int max, const std::wstring& prompt) {
    int v = min;
    std::wstring line;
    while (true) {
        std::wcout << prompt;
        if (!std::getline(std::wcin, line)) {
            return min;
        }
        try {
            v = std::stoi(std::string(line.begin(), line.end()));
        }
        catch (...) {
            std::wcout << L"Invalid input. Try again.\n";
            continue;
        }
        if (v < min || v > max) {
            std::wcout << L"Out of range [" << min << L"," << max << L"].\n";
            continue;
        }
        return v;
    }
}

wchar_t UserInput::getChar(const std::wstring& prompt) {
    std::wstring line;
    while (true) {
        std::wcout << prompt;
        std::getline(std::wcin, line);
        if (line.size() == 1)
            return towupper(line[0]);
        std::wcout << L"Enter exactly one character.\n";
    }
}

std::wstring UserInput::getLine(const std::wstring& prompt) {
    std::wstring line;
    std::wcout << prompt;
    std::getline(std::wcin, line);
    return line;
}
