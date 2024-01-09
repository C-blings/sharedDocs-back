#pragma once

#include <web/request_handlers/RequestHandlersContainerBase.hpp>

namespace web_layout{

    class CORSContainer : public RequestHandlersContainerBase {
    public:
        CORSContainer() {
            // create a container with handlers
            Container container;
            container.AddValue({HandlerMatcher(Method::OPTIONS, std::regex(".*")), CORSHandler});
            SetContainer(container);
        }

    private:
        // request handler
        static HttpResponse CORSHandler(const HttpRequest& request) {
            std::unordered_map<std::string, std::string> headers = {
                    {"Access-Control-Allow-Methods", "GET, POST, OPTIONS"},
                    {"Access-Control-Allow-Headers", "Content-Type"},
                    {"Access-Control-Allow-Origin", "*"}
            };
            return HttpResponse(200, "OK", headers, "CORS");
        }
    };
}
