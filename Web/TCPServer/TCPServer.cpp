#include "TCPServer.hpp"

namespace web_layout{

    TCPServer::TCPServer(const std::string& ip_address, int port) :
                ip_address_(ip_address), port_(port){
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

    void TCPServer::StartListen(){
        listen(socket_, MAX_USERS_COUNT);

        while(1)
        {
            listener_ = accept(socket_, NULL, NULL);

            if(listener_ < 0)
            {
                perror("accept");
                exit(3);
            }

            // handle user
        }
    }
}; // namespace web_layout