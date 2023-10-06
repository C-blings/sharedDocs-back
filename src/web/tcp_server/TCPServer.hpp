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
#include "../models/handlers/WebHandler.hpp"

namespace web_layout
{
    constexpr int MAX_USERS_COUNT = 100;
    constexpr int MAX_REQUEST_SIZE = 1024;


    class TCPServer{
        public:
            explicit TCPServer(const std::string& ip_address, int port);

            void StartListen(HandlerBase* handler) {
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
                    size_t request_size = recv(listener_, request_buffer, MAX_REQUEST_SIZE, 0);
                    HttpRequest request = HttpRequestParser::GetHttpRequest(request_buffer, request_size);

                    std::string response = handler->HandleRequest(request).AsString();

                    if(send(listener_, response.c_str(), response.size(), 0) < 0){
                        perror("sending answer");
                        exit(4);
                    }

                    close(listener_);
                }
            }

            ~TCPServer(){
                close(listener_);
            }

        private:
            const std::string ip_address_;
            const int port_;
            int socket_;
            int listener_;
    };
}; // namespace web_layout
