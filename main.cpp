#include <web/helpers/HandlerMatcher.hpp>
#include <web/request_handlers/RequestHandlersContainerBase.hpp>
#include <web/tcp_server/TCPServer.hpp>
#include <web/request_handlers/BasicContainer.hpp>
#include <web/request_handlers/CORSContainers.hpp>
#include <logging/Logger.hpp>

int main() {
    std::vector<web_layout::RequestHandlersContainerBase> requests_containers = {
web_layout::BasicContainer(),web_layout::CORSContainer(),
   };

    web_layout::Container full_container;

    for (const web_layout::RequestHandlersContainerBase& container_base : requests_containers){
        full_container.AddValues(container_base.GetContainer());
    }

    web_layout::RouterBase router(full_container);
    Logger(Debug).Print("Server restart");
    web_layout::TCPServer server("127.0.0.1", 80);
    std::shared_ptr<web_layout::WebServer> handler = std::make_shared<web_layout::WebServer>(router);

    server.StartListen(handler);
    return 0; 
}