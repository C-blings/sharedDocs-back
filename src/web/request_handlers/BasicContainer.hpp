#pragma once

#include "RequestHandlersContainerBase.hpp"

namespace web_layout{

    class BasicContainer : public RequestHandlersContainerBase {
    public:
        BasicContainer(){
            Container container;
            container.AddValue({HandlerMatcher(Method::GET, std::regex("/")), RootHandler});

            SetContainer(container);
        }

    private:
        static HttpResponse RootHandler (const HttpRequest& request) {
            return HttpResponse(200, "OK", {{"Cache-Control", "no-cache, private"}, {"Content-Type", "text/html"}}, "hello from Sliderer");
        }
    };
}
