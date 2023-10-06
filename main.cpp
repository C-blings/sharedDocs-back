#include <iostream>
#include "src/web/tcp_server/TCPServer.hpp"
#include "src/web/models/handlers/WebHandler.hpp"

int main(){
    web_layout::TCPServer server("127.0.0.1", 80);
    web_layout::WebHandler* handler = new web_layout::WebHandler();

    server.StartListen(handler);

    return 0;
}