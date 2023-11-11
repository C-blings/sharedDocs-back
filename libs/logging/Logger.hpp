#pragma once

#include <ostream>
#include <iostream>
#include <fstream>
#include <unordered_map>

enum LogLevel{
    Debug,
    Warning,
    Error
};

class Logger {
public:
    Logger(LogLevel log_level);

    void operator<<(const std::string& value) const;

private:
    std::string FormatPrefix() const;

    void WriteToFile(const std::string& file_name, const std::string& value) const;

    std::string GetDateTime() const;

private:
    LogLevel log_level_;
    std::unordered_map<LogLevel, std::string> enum_to_string_;
    std::unordered_map<LogLevel, std::string> enum_to_file_path_;
    std::ostream* console_stream_;

    const std::string DEFAULT_LOGS = "logs/default_logs.txt";
    const std::string DEBUG_LOGS = "logs/debug_logs.txt";
    const std::string WARNING_LOGS = "logs/warning_logs.txt";
    const std::string ERROR_LOGS = "logs/error_logs.txt";

    const std::string DATE_TIME_FORMAT = "%Y-%m-%d %H:%M:%S";
};

