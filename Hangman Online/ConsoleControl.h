
//------------------------------------------------------------------------------
// ConsoleControl.h
//------------------------------------------------------------------------------
#pragma once

class ConsoleControl {
public:
    enum class Color { DEFAULT, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, WHITE, BLACK };

    static void setTextColor(Color color);
    static void setBackgroundColor(Color color);
    static void resetColors();
    static void clearScreen();
    static void setCursorPosition(short x, short y);

private:
    static WORD getColorAttribute(Color color);
};
