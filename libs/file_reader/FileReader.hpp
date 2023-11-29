#pragma once

#include <filesystem>
#include <fstream>
#include <vector>


namespace file_reader{
    class FileReader{
    public:
        FileReader() = delete;

        FileReader(const std::filesystem::path& file_path);

        std::string GetFileText() const { return text_; }

        std::vector<std::string> GetFileTextParts(const std::string& splitter) const;

    private:
        std::string text_;
    };
}