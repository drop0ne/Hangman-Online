//------------------------------------------------------------------------------
// ConsoleControl.cpp
//------------------------------------------------------------------------------
#include "PCH.h"
#include "ConsoleControl.h"

void ConsoleControl::setTextColor(Color color) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    if (h == INVALID_HANDLE_VALUE) return;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(h, &csbi)) return;
    WORD bg = csbi.wAttributes & 0xF0;
    SetConsoleTextAttribute(h, bg | getColorAttribute(color));
}

void ConsoleControl::setBackgroundColor(Color color) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    if (h == INVALID_HANDLE_VALUE) return;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(h, &csbi)) return;
    WORD fg = csbi.wAttributes & 0x0F;
    SetConsoleTextAttribute(h, fg | (getColorAttribute(color) << 4));
}

void ConsoleControl::resetColors() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    if (h != INVALID_HANDLE_VALUE)
        SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void ConsoleControl::clearScreen() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    if (h == INVALID_HANDLE_VALUE) return;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(h, &csbi)) return;
    DWORD cells = csbi.dwSize.X * csbi.dwSize.Y, written;
    COORD home = { 0,0 };
    FillConsoleOutputCharacter(h, L' ', cells, home, &written);
    FillConsoleOutputAttribute(h, csbi.wAttributes, cells, home, &written);
    SetConsoleCursorPosition(h, home);
}

void ConsoleControl::setCursorPosition(short x, short y) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    if (h != INVALID_HANDLE_VALUE) {
        COORD pos = { x, y };
        SetConsoleCursorPosition(h, pos);
    }
}

WORD ConsoleControl::getColorAttribute(Color c) {
    switch (c) {
    case Color::RED:     return FOREGROUND_RED | FOREGROUND_INTENSITY;
    case Color::GREEN:   return FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    case Color::BLUE:    return FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    case Color::YELLOW:  return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    case Color::MAGENTA: return FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    case Color::CYAN:    return FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    case Color::WHITE:   return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    case Color::BLACK:   return 0;
    default:             return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    }
}
