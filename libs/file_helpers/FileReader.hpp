#pragma once

#include <filesystem>
#include <fstream>
#include <vector>


namespace file_helpers{
    class FileReader{
    public:
        FileReader() = delete;

        FileReader(const std::filesystem::path& file_path);

        std::string GetFileText() const { return ReadFile(); }

        std::vector<std::string> GetFileTextParts(const std::string& splitter) const;

    private:
        std::string ReadFile() const;

    private:
        std::filesystem::path file_path_;
    };
}