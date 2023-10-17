#pragma once

#include "RequestHandlersContainerBase.hpp"

namespace web_layout{

    class BasicContainer : public RequestHandlersContainerBase {
    private:

        public:
        static HttpResponse RootHandler (const HttpRequest& request) {
            return HttpResponse( "", "", "");
        }

            BasicContainer() : RequestHandlersContainerBase({
                {HandlerMatcher(Method::GET, std::regex("\/")), RootHandler}
            }){
        }
    };
}
