#include "PCH.h"
#include "UserInput.h"

// Log function placeholder for future implementation
// For now, it logs to the console. Later, it can be extended to log to a file.
void logError(const std::string& message) {
    // Placeholder for logging system.
    // For now, we're just logging to the console.
    std::cout << "[LOG ERROR]: " << message << "\n";

    // Future extension: Save to file
    // std::ofstream logFile("error_log.txt", std::ios::app);
    // if (logFile.is_open()) {
    //     logFile << message << "\n";
    // }
    // logFile.close();
}

int UserInput::getIntInRange(int min, int max, const std::string& prompt) {
    int value;
    std::string line;
    while (true) {
        std::cout << prompt;

        if (!std::getline(std::cin, line)) {
            // Handle EOF or input error
            logError("Input failed (EOF or other input error). Returning default value: " + std::to_string(min));
            return min; // Returning default value as a fallback for error
        }

        try {
            size_t pos;
            value = std::stoi(line, &pos);

            // Check for any non-numeric characters after the number
            if (pos != line.size()) {
                throw std::invalid_argument("Extra characters detected after number");
            }
        }
        catch (const std::invalid_argument& e) {
            // Log error and show user-friendly message
            std::string errorMessage = "Invalid number: " + std::string(e.what()) + " (Input: '" + line + "')";
            logError(errorMessage);
            std::cout << "Invalid input. Please enter a valid number.\n";
        }
        catch (const std::out_of_range& e) {
            // Log error and show user-friendly message
            std::string errorMessage = "Number out of range: " + std::string(e.what()) + " (Input: '" + line + "')";
            logError(errorMessage);
            std::cout << "Input number out of range. Please enter a number between " << min << " and " << max << ".\n";
        }

        // Ensure the number is within the expected range
        if (value < min || value > max) {
            std::string errorMessage = "Input value out of range: " + std::to_string(value) + " (Expected range: " + std::to_string(min) + " to " + std::to_string(max) + ")";
            logError(errorMessage);
            std::cout << "Please enter a number between " << min << " and " << max << ".\n";
            continue;
        }

        // Successfully validated, return the value
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