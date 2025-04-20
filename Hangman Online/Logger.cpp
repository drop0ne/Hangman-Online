
//------------------------------------------------------------------------------
// Logger.cpp
//------------------------------------------------------------------------------
// Logger.cpp
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

    // Get current system time
    auto now = std::chrono::system_clock::now();
    auto t_c = std::chrono::system_clock::to_time_t(now);

    // Use the secure localtime_s variant
    std::tm tm_buf;
    if (localtime_s(&tm_buf, &t_c) != 0) {
        // Fallback: zero out on error
        tm_buf = std::tm{};
    }

    // Format and write timestamp
    logFile
        << std::put_time(&tm_buf, "%F %T")
        << " [" << level << "] " << message << "\n";
}
