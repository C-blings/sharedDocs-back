#include <iostream>
#include "src/web/tcp_server/TCPServer.hpp"
#include "src/web/models/servers/WebServer.hpp"
#include "src/web/models/routers/RouterBase.hpp"
#include "src/web/request_handlers/BasicContainer.hpp"

int main(){
    web_layout::BasicContainer basic;
    web_layout::RouterBase router(basic.GetContainer());

    web_layout::TCPServer server("127.0.0.1", 80);
    web_layout::WebServer* handler = new web_layout::WebServer(router);

    server.StartListen(handler);

    return 0;
}