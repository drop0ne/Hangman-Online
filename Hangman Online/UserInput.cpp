#include "PCH.h"
#include "UserInput.h"

int UserInput::getIntInRange(int min, int max, const std::string& prompt)
{
    int value;
    std::string line;
    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, line)) {
            // Handle EOF or input error if needed
            return min; // default or break
        }
        try {
            size_t pos;
            value = std::stoi(line, &pos);
            if (pos != line.size()) throw std::invalid_argument("Extra characters");
        }
        catch (const std::invalid_argument& e) {
            std::cout << "Invalid number: " << e.what() << "\n";
        }
        catch (const std::out_of_range& e) {
            std::cout << "Number out of range: " << e.what() << "\n";
        }
        if (value < min || value > max) {
            std::cout << "Please enter a number between " << min << " and " << max << ".\n";
            continue;
        }
        return value;
    }
}

char UserInput::getChar(const std::string& prompt, const std::string& validChars) {
#undef max // Avoid macro conflict
    char input;
    while (true) {
        std::cout << prompt;
        if (std::cin >> input) {
            if (validChars.find(input) != std::string::npos) {
                return input;
            }
            else {
                std::cout << "Please enter a valid character from the following: " << validChars << "\n";
            }
        }
        else {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
            std::cout << "Invalid input. Please try again.\n";
        }
    }
}

std::string UserInput::getLine(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);  // Get the full line of input

    // Optional: trim the input
    input = trim(input);

    return input;
}

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r\f\v"); // Find the first non-whitespace character
    if (first == std::string::npos) {
        return ""; // No non-whitespace characters found
    }
    size_t last = str.find_last_not_of(" \t\n\r\f\v"); // Find the last non-whitespace character
    return str.substr(first, last - first + 1); // Return the trimmed substring
}