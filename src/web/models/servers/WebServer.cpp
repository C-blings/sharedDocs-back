#pragma once

#include "WebServer.hpp"
#include "../routers/RouterBase.hpp"

namespace web_layout{
    HttpResponse WebServer::HandleRequest(const HttpRequest& request){
        auto handler = router_.GetRequestHandler(request);
        return handler(request);
    }
} // namespace web_layout
