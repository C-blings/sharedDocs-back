#pragma once

#include <web/request_handlers/RequestHandlersContainerBase.hpp>

namespace web_layout{

    class TestContainer : public RequestHandlersContainerBase {
    public:
        TestContainer(){
            Container container;
            container.AddValue({HandlerMatcher(Method::GET, "/"), RootHandler});

            SetContainer(container);
        }

    private:
        static HttpResponse RootHandler (const HttpRequest& request) {
            std::unordered_map<std::string, std::string> headers = {
                    {"Access-Control-Allow-Origin", "*"},
                    {"Content-Type", "application/json"}
            };

            return HttpResponse(200, "OK", headers, "{\"message\": \"hello from Sliderer\"}");
        }
    };
}
