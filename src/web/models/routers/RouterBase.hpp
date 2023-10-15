#pragma once

#include <unordered_map>
#include <functional>
#include "../HttpRequest.hpp"
#include "../handlers/HandlerMatcher.hpp"
#include "../HttpResponse.hpp"

namespace web_layout{
    class RouterBase {
        using RequestHandlerType = std::function<HttpResponse (const HttpRequest&)>;
        using RouterType = std::unordered_map<HandlerMatcher, RequestHandlerType>;
    public:

        RouterBase(const RouterType& route_map) : route_map_(route_map) {}

        RequestHandlerType GetRequestHandler(const HttpRequest& request) const {
            RequestHandlerType* founded_handler = nullptr;
            for (auto [matcher, handler] : route_map_){
                if(matcher.Match(request)){
                    founded_handler = &handler;
                }
            }

            if (!founded_handler){
                throw std::runtime_error("No handler founded");
            }else{
                return *founded_handler;
            }
        };

    private:
        const RouterType route_map_;
    };
}
