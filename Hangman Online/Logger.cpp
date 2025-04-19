#include "PCH.h"
#include "Logger.h"

void logError(const std::string& message) {
	log("ERROR", message);
}

void logInfo(const std::string& message) {
	log("INFO", message);
}

void log(const std::string& level, const std::string& message) {
	std::ofstream logFile("error_log.txt", std::ios_base::app);
	if (!logFile) {
		std::cerr << "Error: Could not open log file\n";
		return;
	}

	std::time_t now = std::time(nullptr);
	logFile << std::ctime(&now) << " [" << level << "] " << message << "\n";
}
