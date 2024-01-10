#pragma once

#include <web/request_handlers/RequestHandlersContainerBase.hpp>

namespace web_layout{

    class CORSContainer : public RequestHandlersContainerBase {
    public:
        CORSContainer();

    private:
        // request handler
        static HttpResponse CORSHandler(const HttpRequest& request);
    };
}
