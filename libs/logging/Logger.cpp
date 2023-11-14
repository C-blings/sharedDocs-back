#define FMT_HEADER_ONLY

#include "Logger.hpp"

#include <sstream>
#include <fmt/format.h>
#include <chrono>

Logger::Logger(LogLevel log_level) : log_level_(log_level) {
        console_stream_ = &std::cout;
        enum_to_string_ = {
            {Debug, "DEBUG"},
            {Warning, "WARNING"},
            {Error, "ERROR"}
        };
        enum_to_file_path_ = {
            {Debug, DEBUG_LOGS},
            {Warning, WARNING_LOGS},
            {Error, ERROR_LOGS}
        };
}

std::string Logger::FormatPrefix() const{
    return fmt::format("[ {} {} ] ", GetDateTime(), enum_to_string_.at(log_level_));
}

std::string Logger::GetDateTime() const{
    std::time_t time = std::chrono::system_clock::to_time_t(
            std::chrono::system_clock::now()
    );
    char buffer[90];
    tm* time_info = localtime(&time);
    strftime(buffer, sizeof(buffer), DATE_TIME_FORMAT.c_str(), time_info);
    return buffer;
}

void Logger::WriteToFile(const std::string& file_name, const std::string& value) const{
    std::ofstream output_file(file_name, std::ios::app);
    output_file << value;
    output_file.close();
}