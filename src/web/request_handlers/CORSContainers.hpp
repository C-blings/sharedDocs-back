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
                    {"Cache-Control", "max-age=604800, must-revalidate"},
                    {"Age:", "100"},
                    {"Access-Control-Allow-Origin", "*"},
                    {"Access-Control-Allow-Methods", "POST, GET, OPTIONS"},
                    {"Access-Control-Allow-Headers", "Content-Type"}
            };
            return HttpResponse(200, "OK", headers, "CORS");
        }
    };
}
