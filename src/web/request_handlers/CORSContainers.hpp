#pragma once

#include "RequestHandlersContainerBase.hpp"

namespace web_layout{

    class CORSContainer : public RequestHandlersContainerBase {
    public:
        CORSContainer() : RequestHandlersContainerBase(Container({
            {HandlerMatcher(Method::GET, std::regex(".*")), RootHandler}
        })) {}

    private:
        static HttpResponse CORSHandler(const HttpRequest& request) {
            return HttpResponse(200, "OK", {{"Cache-Control", "no-cache, private"}, {"Content-Type", "text/html"}}, "CORS DONE!");
        }
    };
}
