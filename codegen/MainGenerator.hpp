#pragma once

#include <sstream>
#include <iostream>
#include <RequestHandlersParser.hpp>

namespace codegen{
    class MainGenerator{
    public:
        MainGenerator() = delete;

        static void GenerateMain(){
            std::ostringstream stream;
            FillIncludes(stream);
            FillMainFunction(stream);
            std::cout << stream.str() << '\n';
        }

    private:

        static void FillMainFunction(std::ostream& stream){
            stream << "int main() {\n";
            const std::vector<std::string> handlers = RequestHandlersParser::ParseRequestHandlers(kHandlersDirectory);

            stream << "    std::vector<web_layout::RequestHandlersContainerBase> requests_containers = {\n"
            "           BasicContainer(), web_layout::CORSContainer(),\n";
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
            "    Logger(Debug).Print(\"Server restart\");\n"
            "    web_layout::TCPServer server(\"127.0.0.1\", 80);\n"
            "    std::shared_ptr<web_layout::WebServer> handler = std::make_shared<web_layout::WebServer>(router);\n"
            "\n"
            "    server.StartListen(handler);";

            stream << "return 0; \n}";
        }

        static void FillIncludes(std::ostringstream& stream){
            stream << "#include <web/helpers/HandlerMatcher.hpp>\n" <<
            "#include <web/request_handlers/RequestHandlersContainerBase.hpp>\n" <<
            "#include <web/tcp_server/TCPServer.hpp>\n" <<
            "#include <web/request_handlers/BasicContainer.hpp>\n" <<
            "#include <web/request_handlers/CORSContainers.hpp>\n" <<
            "#include <logging/Logger.hpp>\n\n";
        }

    private:
        static const std::vector<std::string> kHandlersDirectory;
    };
}