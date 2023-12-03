#include "RequestHandlersParser.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>

#include <file_helpers/FileReader.hpp>

namespace codegen{
    const std::string RequestHandlersParser::kBasicClassName = "RequestHandlersContainerBase";

    std::vector<std::string> RequestHandlersParser::ParseRequestHandlers(const std::vector<std::string>& paths) {
        std::vector<std::string> result;
        for(const std::string& path : paths){
            std::vector<std::string> directory_handlers = ParseDirectory(path);
            for (auto& handler : directory_handlers){
                result.emplace_back(std::move(handler));
            }
        }

        return result;
    }


    std::vector<std::string> RequestHandlersParser::ParseDirectory(const std::string& path) {
        std::filesystem::path directory = path;

        if (!std::filesystem::exists(directory) ||
            !std::filesystem::is_directory(directory)){
            throw std::runtime_error("can not open directory");
        }

        std::vector<std::string> result;
        for(auto file : std::filesystem::directory_iterator(directory)){
            if (std::filesystem::is_regular_file(file)){
                std::vector<std::string> file_handlers = ParseFile(file);
                for(auto& current_class : file_handlers){
                    result.emplace_back(std::move(current_class));
                }
            }
        }

        return result;
    }

    std::vector<std::string> RequestHandlersParser::ParseFile(const std::filesystem::path& file_path) {
        file_helpers::FileReader file_reader(file_path);
        std::vector<std::string> file_parts = file_reader.GetFileTextParts(" ");

        std::vector<std::string> result;
        for (int i = 0; i < file_parts.size(); ++i){
            if (file_parts[i] == "class" &&
                i + 4 < file_parts.size() &&
                file_parts[i + 4] == kBasicClassName){

                result.push_back(file_parts[i + 1]);
            }
        }
        return result;
    }
}
