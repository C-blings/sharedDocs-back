#include "FileReader.hpp"

#include <boost/algorithm/string.hpp>

namespace file_helpers{
    std::vector<std::string> FileReader::GetFileTextParts(const std::string& splitter) const {
        std::vector<std::string> text_parts;
        std::string text = ReadFile();
        boost::split(text_parts, text, boost::is_any_of(splitter), boost::token_compress_off);
        return text_parts;
    }

    FileReader::FileReader(const std::filesystem::path& file_path) : file_path_(file_path) {}

    std::string FileReader::ReadFile() const{
        if (!std::filesystem::exists(file_path_) ||
            !std::filesystem::is_regular_file(file_path_)){
            throw std::runtime_error("Not relevant file path: not exists or not regular file");
        }

        std::ifstream file(file_path_.c_str(), std::ios::out);

        if (!file.is_open()){
            throw std::runtime_error("Can not open file");
        }

        std::ostringstream file_stream;
        file_stream << file.rdbuf();
        std::string result = file_stream.str();

        file.close();

        return result;
    }
}