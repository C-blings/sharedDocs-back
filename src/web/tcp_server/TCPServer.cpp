#include "TCPServer.hpp"

#include <logging/Logger.hpp>

namespace web_layout{

    TCPServer::TCPServer(const std::string& ip_address, int port) :
                ip_address_(ip_address), port_(port), active_(true){
        sockaddr_in addr;

        socket_ = socket(AF_INET, SOCK_STREAM, 0);
        if(socket_ < 0)
        {
            perror("socket");
            exit(1);
        }

        addr.sin_family = AF_INET;
        addr.sin_port = htons(port_);
        inet_pton(AF_INET, ip_address_.c_str(), &addr.sin_addr);
        if(bind(socket_, (sockaddr *)&addr, sizeof(addr)) < 0)
        {
            perror("bind");
            exit(2);
        }
    }

    void TCPServer::StartListen(std::shared_ptr<ServerBase> handler) {
        listen(socket_, MAX_USERS_COUNT);

        char request_buffer[MAX_REQUEST_SIZE];

        while(active_)
        {
            listener_ = accept(socket_, NULL, NULL);

            if(listener_ < 0)
            {
                perror("accept");
                exit(3);
            }

            // handle user
            size_t request_size = recv(listener_, request_buffer, MAX_REQUEST_SIZE, 0);
            HttpRequest request = HttpRequestParser::GetHttpRequest(request_buffer);
            Logger(Debug).Print(request_buffer);
            std::string response = handler->HandleRequest(request).AsString();

            if(send(listener_, response.c_str(), response.size(), 0) < 0){
                perror("sending answer");
                exit(4);
            }

            close(listener_);
        }
    }
}; // namespace web_layout