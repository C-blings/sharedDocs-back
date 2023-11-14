#include <iostream>
#include "src/web/helpers/HandlerMatcher.hpp"
#include "src/web/request_handlers/RequestHandlersContainerBase.hpp"
#include "src/web/tcp_server/TCPServer.hpp"
#include "src/web/models/servers/WebServer.hpp"
#include "src/web/models/routers/RouterBase.hpp"
#include "src/web/request_handlers/BasicContainer.hpp"

int main(){
    std::vector<web_layout::RequestHandlersContainerBase> requests_containers = {
            web_layout::BasicContainer(),
    };

    web_layout::Container full_container;

    for (const web_layout::RequestHandlersContainerBase& container_base : requests_containers){
        full_container.AddValues(container_base.GetContainer());
    }

    web_layout::RouterBase router(full_container);
    
    web_layout::TCPServer server("127.0.0.1", 80);
    web_layout::WebServer* handler = new web_layout::WebServer(router);

    server.StartListen(handler);

    return 0;
}
