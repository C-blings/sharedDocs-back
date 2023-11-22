#pragma once

#include <string>                                                                            
#include <sys/socket.h>
#include <netinet/in.h>
#include <csignal>
#include <cstdlib>
#include <cstdio>
#include <arpa/inet.h>
#include <memory>
#include <iostream>

#include <web/models/servers/ServerBase.hpp>
#include <web/helpers/HttpRequestParser.hpp>
#include <web/models/servers/WebServer.hpp>
#include <web/models/routers/RouterBase.hpp>

namespace web_layout
{
    constexpr int MAX_USERS_COUNT = 100;
    constexpr int MAX_REQUEST_SIZE = 1024;


    class TCPServer{
        public:
            explicit TCPServer(const std::string& ip_address, int port);

            void StartListen(std::shared_ptr<ServerBase> handler);

            ~TCPServer(){
                close(listener_);
            }

        private:
            const std::string ip_address_;
            const int port_;
            int socket_;
            int listener_;
            bool active_;
    };
}; // namespace web_layout
