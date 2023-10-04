#pragma once

#include <string>                                                                            
#include <sys/socket.h>
#include <netinet/in.h>
#include <csignal>
#include <cstdlib>
#include <cstdio>
#include <arpa/inet.h>
#include <iostream>

namespace web_layout
{
    constexpr int MAX_USERS_COUNT = 100;

    class TCPServer{
        public:
            explicit TCPServer(const std::string& ip_address, int port);

            void StartListen();

        private:
            const std::string ip_address_;
            const int port_;
            int socket_;
            int listener_;
    };
}; // namespace web_layout
