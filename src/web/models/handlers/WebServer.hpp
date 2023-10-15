#pragma once

#include "ServerBase.hpp"
#include "../routers/RouterBase.hpp"

namespace web_layout{

    class WebServer : public ServerBase{
        public:
         WebServer(const RouterBase& router) : router_(router) {}

         HttpResponse HandleRequest(const HttpRequest& request) override;

        private:
            RouterBase router_;
    };

} // namespace web_layout