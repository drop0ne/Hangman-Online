// ConsoleControl.h
#pragma once
#include "PCH.h"

/**
 * @brief Utility class for controlling console screen behavior.
 *
 * Provides methods to clear the screen, set cursor position,
 * and internally wraps WinAPI calls with exception-based error
 * handling.
 */
class ConsoleControl {
public:
    // Color constants (could map to DWORD values or custom enum)
    enum class Color { DEFAULT, RED, GREEN, BLUE, YELLOW, WHITE, BLACK };

    // Set text (foreground) color
    static void setTextColor(Color color);

    // Set background color
    static void setBackgroundColor(Color color);

    /**
     * @brief Clears the entire console screen and resets the cursor
     *        to the top-left corner.
     *
     * Retrieves the console output handle, obtains screen buffer
     * information (size and current attributes), fills the buffer
     * with spaces using existing color attributes, and positions
     * the cursor at (0,0).  Any underlying WinAPI error is caught
     * and reported without bubbling exceptions further.
     */
    static void clearScreen();

    /**
     * @brief Retrieves the handle to the console output.
     * @return A valid HANDLE to standard output.
     * @throws std::runtime_error if GetStdHandle fails.
     */
    static HANDLE getConsoleHandle();

    /**
     * @brief Retrieves screen buffer information for the console.
     * @param hConsole  Handle to the console output.
     * @return CONSOLE_SCREEN_BUFFER_INFO struct with size and attributes.
     * @throws std::runtime_error if GetConsoleScreenBufferInfo fails.
     */
    static CONSOLE_SCREEN_BUFFER_INFO getScreenBufferInfo(HANDLE hConsole);

    /**
     * @brief Fills the console screen with a given character.
     * @param hConsole  Handle to the console output.
     * @param ch        Character to write (e.g., space).
     * @param length    Number of characters to fill.
     * @param coord     Starting coordinate for filling.
     * @throws std::runtime_error if FillConsoleOutputCharacter fails.
     */
    static void fillOutputCharacter(HANDLE hConsole, TCHAR ch, DWORD length, COORD coord);

    /**
     * @brief Fills the console screen with a given attribute.
     * @param hConsole   Handle to the console output.
     * @param attributes Attribute (color) to apply.
     * @param length     Number of cells to fill.
     * @param coord      Starting coordinate for filling.
     * @throws std::runtime_error if FillConsoleOutputAttribute fails.
     */
    static void fillOutputAttribute(HANDLE hConsole, WORD attributes, DWORD length, COORD coord);

    /**
     * @brief Sets the console cursor to a specific coordinate.
     * @param hConsole  Handle to the console output.
     * @param coord     Target cursor position.
     * @throws std::runtime_error if SetConsoleCursorPosition fails.
     */
    static void setCursorPosition(HANDLE hConsole, COORD coord);

private:
    // Helper to convert Color enum to console color attributes
    static WORD getColorAttributes(Color color);
};