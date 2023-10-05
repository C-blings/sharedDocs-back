#pragma once

#include <string>                                                                            
#include <sys/socket.h>
#include <netinet/in.h>
#include <csignal>
#include <cstdlib>
#include <cstdio>
#include <arpa/inet.h>
#include <iostream>

#include "../models/handlers/HandlerBase.hpp"
#include "../helpers/HttpRequestParser.hpp"

namespace web_layout
{
    constexpr int MAX_USERS_COUNT = 100;
    constexpr int MAX_REQUEST_SIZE = 1024;


    class TCPServer{
        public:
            explicit TCPServer(const std::string& ip_address, int port);

            template<class HandlerType>
            void StartListen(HandlerType handler) {
                listen(socket_, MAX_USERS_COUNT);

                char request_buffer[MAX_REQUEST_SIZE];

                while(1)
                {
                    listener_ = accept(socket_, NULL, NULL);

                    if(listener_ < 0)
                    {
                        perror("accept");
                        exit(3);
                    }

                    // handle user
                    int request_size = recv(listener_, request_buffer, MAX_REQUEST_SIZE, 0);
                    HttpRequest request = HttpRequestParser::GetHttpRequest(request_buffer, request_size);
                    char* response = handler.HandleRequest(request);
                    send(listener_, response, sizeof(response), 0);
                }
            }

        private:
            const std::string ip_address_;
            const int port_;
            int socket_;
            int listener_;
    };
}; // namespace web_layout
