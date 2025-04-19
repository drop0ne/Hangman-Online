#include "PCH.h"
#include "Logger.h"


void Logger::logError(const std::string& message) {
	log("ERROR", message);
}

void Logger::logInfo(const std::string& message) {
	log("INFO", message);
}

void Logger::log(const std::string& level, const std::string& message) {
    std::ofstream logFile("error_log.txt", std::ios_base::app);
    if (!logFile) {
        std::cerr << "Error: Could not open log file\n";
        return;
    }

    // Get the current time using std::chrono
    auto now = std::chrono::system_clock::now();

    // Get epoch time (seconds since epoch)
    auto epoch_time = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();

    // Write the log message with the epoch time
    logFile << "Epoch Time: " << epoch_time << " [" << level << "] " << message << "\n";
}