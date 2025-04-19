#pragma once
class Logger
{
public:
	static void logError(const std::string& message);
	static void logInfo(const std::string& message);
private:
	static void log(const std::string& level, const std::string& message);
};

