#include "FileReader.hpp"

#include <boost/algorithm/string.hpp>

namespace file_reader{
    std::vector<std::string> FileReader::GetFileTextParts(const std::string& splitter) const {
        std::vector<std::string> text_parts;
        boost::split(text_parts, text_, boost::is_any_of(splitter), boost::token_compress_off);
        return text_parts;
    }

    FileReader::FileReader(const std::filesystem::path& file_path){
        if (!std::filesystem::exists(file_path) ||
            !std::filesystem::is_regular_file(file_path)){
            throw std::runtime_error("Not relevant file path: not exists or not regular file");
        }

        std::ifstream file(file_path.c_str());
        std::ostringstream file_stream;
        file_stream << file.rdbuf();
        text_ = file_stream.str();
    }
}