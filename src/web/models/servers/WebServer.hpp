#pragma once

#include <web/models/servers/ServerBase.hpp>
#include <web/models/routers/RouterBase.hpp>

namespace web_layout{

    class WebServer : public ServerBase{
    public:
     WebServer(const RouterBase& router) : router_(router) {}

     HttpResponse HandleRequest(const HttpRequest& request) const override;

    private:
        RouterBase router_;
    };

} // namespace web_layout