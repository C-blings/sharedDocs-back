#include <iostream>
#include "src/web/tcp_server/TCPServer.hpp"
#include "src/web/models/handlers/WebServer.hpp"
#include "src/web/models/routers/RouterBase.hpp"

int main(){
    web_layout::RouterBase router = {};

    web_layout::TCPServer server("127.0.0.1", 80);
    web_layout::WebServer* handler = new web_layout::WebServer(router);

    server.StartListen(handler);

    return 0;
}