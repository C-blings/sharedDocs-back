#pragma once

#include <map>
#include <functional>
#include "../HttpRequest.hpp"
#include "../../helpers/HandlerMatcher.hpp"
#include "../HttpResponse.hpp"

namespace web_layout{
    using RequestHandler = std::function<HttpResponse (const HttpRequest&)>;
    struct Node{
        HandlerMatcher matcher;
        RequestHandler handler;
    };
    using Container = std::vector<Node>;

    class RouterBase {
        public:

            RouterBase(const Container& route_map) : route_map_(route_map) {}

            RequestHandler GetRequestHandler(const HttpRequest& request) const {
                RequestHandler* founded_handler = nullptr;
                for (auto [matcher, handler] : route_map_){
                    if(matcher.Match(request)){
                        founded_handler = &handler;
                    }
                }

                if (!founded_handler){
                    throw std::runtime_error("No handler founded ");
                }else{
                    return *founded_handler;
                }
            };

        private:
            const Container route_map_;
    };
}
