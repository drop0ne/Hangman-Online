#include "PCH.h"
#include "ConsoleControl.h"

void ConsoleControl::clearScreen()
{
	try
	{
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
	catch (const std::exception& e)
	{
		// Log the error; clearScreen remains non-throwing
		std::cerr << "[ConsoleControl] clearScreen error: " << e.what() << std::endl;
	}
}

HANDLE ConsoleControl::getConsoleHandle()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE)
	{
		throw std::runtime_error("GetStdHandle(STD_OUTPUT_HANDLE) returned INVALID_HANDLE_VALUE");
	}
	return hConsole;
}

CONSOLE_SCREEN_BUFFER_INFO ConsoleControl::getScreenBufferInfo(HANDLE hConsole)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		throw std::runtime_error("GetConsoleScreenBufferInfo failed");
	}
	return csbi;
}

void ConsoleControl::fillOutputCharacter(HANDLE hConsole, TCHAR ch, DWORD length, COORD coord)
{
	DWORD written = 0;
	if (!FillConsoleOutputCharacter(hConsole, ch, length, coord, &written))
	{
		throw std::runtime_error("FillConsoleOutputCharacter failed");
	}
}

void ConsoleControl::fillOutputAttribute(HANDLE hConsole, WORD attributes, DWORD length, COORD coord)
{
	DWORD written = 0;
	if (!FillConsoleOutputAttribute(hConsole, attributes, length, coord, &written))
	{
		throw std::runtime_error("FillConsoleOutputAttribute failed");
	}
}

void ConsoleControl::setCursorPosition(HANDLE hConsole, COORD coord)
{
	if (!SetConsoleCursorPosition(hConsole, coord))
	{
		throw std::runtime_error("SetConsoleCursorPosition failed");
	}
}
