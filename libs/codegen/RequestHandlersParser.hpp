#pragma once

#include <string>
#include <vector>
#include <filesystem>

namespace codegen{
    class RequestHandlersParser{
    public:
        RequestHandlersParser() = delete;

        static std::vector<std::string> ParseRequestHandlers(const std::vector<std::string>&);

    private:
        static std::vector<std::string> ParseDirectory(const std::string&);

        static std::vector<std::string> ParseFile(const std::filesystem::path&);

    private:
        static const std::string kBasicClassName;
    };
}