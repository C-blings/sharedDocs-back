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
    constexpr int MAX_REQUEST_SIZE = 1024;


    class TCPServer{
        public:
            explicit TCPServer(const std::string& ip_address, int port);

            template<class HandlerType>
            void StartListen(HandlerType handler) const {
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
                    recv(listener_, request_buffer, MAX_REQUEST_SIZE, 0);
                }
            }

        private:
            const std::string ip_address_;
            const int port_;
            int socket_;
            int listener_;
    };
}; // namespace web_layout
