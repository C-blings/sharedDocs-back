#include "RequestHandlersParser.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>

namespace codegen{
    const std::string RequestHandlersParser::kBasicClassName = "RequestHandlersContainerBase";

    std::vector<std::string> RequestHandlersParser::ParseRequestHandlers(const std::vector<std::string>& paths) {
        std::vector<std::string> result;
        for(const std::string& path : paths){
            std::vector<std::string> directory_handlers = ParseDirectory(path);
            for (auto& handler : directory_handlers){
                std::cout << handler << '\n';
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
        std::fstream file(file_path);
        std::string line;
        std::vector<std::string> class_data, result;
        while(file >> line){
            if(class_data.size() < 5 || line == "class"){
                class_data.emplace_back(line);
            } else if (class_data.size() == 5){
                if (class_data.back() == kBasicClassName){
                    result.emplace_back(std::move(class_data.at(1)));
                }
                class_data.clear();
            }
        }
        return result;
    }
}
