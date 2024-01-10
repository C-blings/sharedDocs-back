#pragma once
#define FMT_HEADER_ONLY

#include <sstream>
#include <iostream>
#include <fmt/format.h>
#include <filesystem>

#include <RequestHandlersParser.hpp>
#include <file_helpers/FileReader.hpp>
#include <file_helpers/FileWriter.hpp>
#include <formats/json/Json.hpp>

namespace codegen{
    class MainGenerator{
    public:
        MainGenerator() = delete;

        static void GenerateMain(const std::filesystem::path& config_path, const std::string& file_name){
            std::ostringstream stream;
            FillIncludes(stream);
            FillMainFunction(stream, config_path);
            FillFile(stream.str(), file_name);
        }

    private:

        static void FillFile(const std::string& text, const std::string& file_name){
            file_helpers::FileWriter file_writer(file_name);
            file_writer.WriteToFile(text);
        }

        static void FillMainFunction(std::ostream& stream, const std::filesystem::path& config_path){

            const std::vector<std::string> handlers = RequestHandlersParser::ParseRequestHandlers(kHandlersDirectory);

            if (!std::filesystem::exists(config_path) ||
                !std::filesystem::is_regular_file(config_path)){
                throw std::runtime_error("Can not open config file");
            }

            //parse host and port form config
            file_helpers::FileReader file_reader(config_path);
            std::string text = file_reader.GetFileText();
            formats::json::JsonValue config(text);
            const std::string host = config.GetValue<std::string>("host");
            const int port = config.GetValue<int>("port");

            stream << "int main() {\n";
            // set request handlers array
            stream << "    std::vector<web_layout::RequestHandlersContainerBase> requests_containers = {\n";
            for (const std::string& handler : handlers){
                stream << "web_layout::" << handler << "(),";
            }
            stream << "\n   };\n"
            "\n"
            "    web_layout::Container full_container;\n"
            "\n"
            "    for (const web_layout::RequestHandlersContainerBase& container_base : requests_containers){\n"
            "        full_container.AddValues(container_base.GetContainer());\n"
            "    }\n"
            "\n"
            "    web_layout::RouterBase router(full_container);\n"
            "    Logger(Debug).Print(\"Server restart\");\n";

            stream << fmt::format("    web_layout::TCPServer server(\"{}\", {});\n", host, port);

            stream << "    std::shared_ptr<web_layout::WebServer> handler = std::make_shared<web_layout::WebServer>(router);\n"
            "\n"
            "    server.StartListen(handler);\n";

            stream << "    return 0; \n}";
        }

        static void FillIncludes(std::ostringstream& stream){
            stream << "#include <web/helpers/HandlerMatcher.hpp>\n" <<
            "#include <web/request_handlers/RequestHandlersContainerBase.hpp>\n" <<
            "#include <web/tcp_server/TCPServer.hpp>\n" <<
            "#include <web/request_handlers/TestContainer.hpp>\n" <<
            "#include <web/request_handlers/RegistrationContainers.hpp>\n" <<
            "#include <web/request_handlers/CORSContainers.hpp>\n" <<
            "#include <logging/Logger.hpp>\n\n";
        }

    private:
        static const std::vector<std::string> kHandlersDirectory;
    };
}