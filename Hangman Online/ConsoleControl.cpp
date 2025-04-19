#include "PCH.h"
#ifndef CONSOLECONTROL_HPP
#define CONSOLECONTROL_HPP

#include "ConsoleControl.h"

// Utility function to handle error logging in console control operations
void ConsoleControl::logConsoleControlError(const std::string& function, const std::exception& e) {
    std::cerr << "[ConsoleControl] " << function << " error: " << e.what() << std::endl;
}

void ConsoleControl::setTextColor(Color color)
{
    try {
        HANDLE hConsole = getConsoleHandle();
        WORD attributes = getColorAttributes(color);
        if (!SetConsoleTextAttribute(hConsole, attributes)) {
            throw std::runtime_error("SetConsoleTextAttribute failed");
        }
    }
    catch (const std::exception& e) {
        logConsoleControlError("setTextColor", e);
    }
}

void ConsoleControl::setBackgroundColor(Color color)
{
    try {
        HANDLE hConsole = getConsoleHandle();
        WORD attributes = getColorAttributes(color);

        // Modify to handle background color change separately (background is upper byte)
        attributes |= BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  // Set background attributes
        if (!SetConsoleTextAttribute(hConsole, attributes)) {
            throw std::runtime_error("SetConsoleTextAttribute failed");
        }
    }
    catch (const std::exception& e) {
        logConsoleControlError("setBackgroundColor", e);
    }
}

void ConsoleControl::clearScreen()
{
    try {
        HANDLE hConsole = getConsoleHandle();
        auto csbi = getScreenBufferInfo(hConsole);
        DWORD cellCount = static_cast<DWORD>(csbi.dwSize.X * csbi.dwSize.Y);
        COORD homeCoords = { 0, 0 };

        // 1) Fill the entire buffer with spaces
        fillOutputCharacter(hConsole, TEXT(' '), cellCount, homeCoords);

        // 2) Restore the original text attributes
        fillOutputAttribute(hConsole, csbi.wAttributes, cellCount, homeCoords);

        // 3) Move the cursor to top-left corner
        setCursorPosition(hConsole, homeCoords);
    }
    catch (const std::exception& e) {
        logConsoleControlError("clearScreen", e);
    }
}

HANDLE ConsoleControl::getConsoleHandle()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("GetStdHandle(STD_OUTPUT_HANDLE) returned INVALID_HANDLE_VALUE");
    }
    return hConsole;
}

CONSOLE_SCREEN_BUFFER_INFO ConsoleControl::getScreenBufferInfo(HANDLE hConsole)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        throw std::runtime_error("GetConsoleScreenBufferInfo failed");
    }
    return csbi;
}

void ConsoleControl::fillOutputCharacter(HANDLE hConsole, TCHAR ch, DWORD length, COORD coord)
{
    DWORD written = 0;
    if (!FillConsoleOutputCharacter(hConsole, ch, length, coord, &written)) {
        throw std::runtime_error("FillConsoleOutputCharacter failed");
    }
}

void ConsoleControl::fillOutputAttribute(HANDLE hConsole, WORD attributes, DWORD length, COORD coord)
{
    DWORD written = 0;
    if (!FillConsoleOutputAttribute(hConsole, attributes, length, coord, &written)) {
        throw std::runtime_error("FillConsoleOutputAttribute failed");
    }
}

void ConsoleControl::setCursorPosition(HANDLE hConsole, COORD coord)
{
    if (!SetConsoleCursorPosition(hConsole, coord)) {
        throw std::runtime_error("SetConsoleCursorPosition failed");
    }
}

WORD ConsoleControl::getColorAttributes(Color color)
{
    switch (color)
    {
    case Color::RED:
        return FOREGROUND_RED;
    case Color::GREEN:
        return FOREGROUND_GREEN;
    case Color::BLUE:
        return FOREGROUND_BLUE;
    case Color::YELLOW:
        return FOREGROUND_RED | FOREGROUND_GREEN;
    case Color::WHITE:
        return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    case Color::BLACK:
        return 0; // No color
    case Color::DEFAULT:
    default:
        return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; // Default white
    }
}

#endif // CONSOLECONTROL_HPP