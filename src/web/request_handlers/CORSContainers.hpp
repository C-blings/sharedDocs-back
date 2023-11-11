#pragma once

#include "RequestHandlersContainerBase.hpp"

namespace web_layout{

    class CORSContainer : public RequestHandlersContainerBase {
    public:
        CORSContainer() {
            Container container;
            container.AddValue({HandlerMatcher(Method::OPTIONS, std::regex(".*")), CORSHandler});
            SetContainer(container);
        }

    private:
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
