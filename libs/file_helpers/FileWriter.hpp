#pragma once

#include <filesystem>
#include <fstream>
#include <sstream>

namespace file_helpers{
    class FileWriter{
    public:
        FileWriter(const std::filesystem::path& file_path);

        template<typename T, typename... Args>
        void WriteToFile(T head, Args... args){
            stream_ << head;
            WriteToFile(args...);
        }

        template <typename T>
        void WriteToFile(T value) {
            stream_ << value;
            std::string text = stream_.str();
            stream_.clear();
            if (!std::filesystem::exists(file_path_) ||
                !std::filesystem::is_regular_file(file_path_)){
                throw std::runtime_error("Not relevant file path: not exists or not regular file");
            }

            std::ofstream file(file_path_.c_str());

            if (!file.is_open()){
                throw std::runtime_error("Can not open file");
            }

            file << text;
            file.close();
        }

    private:
        std::filesystem::path file_path_;
        std::stringstream stream_;
    };
}
