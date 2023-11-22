#pragma once

#include <web/models/HttpRequest.hpp>
#include <web/models/HttpResponse.hpp>

namespace web_layout{

    class ServerBase{
    public:
        virtual HttpResponse HandleRequest(const HttpRequest& http_request) = 0;
    };

} // namespace web_layout