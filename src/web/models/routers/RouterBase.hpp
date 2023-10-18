#pragma once

#include <map>
#include <functional>
#include "../HttpRequest.hpp"
#include "../../helpers/HandlerMatcher.hpp"
#include "../HttpResponse.hpp"

namespace web_layout{
    using RequestHandler = std::function<HttpResponse (const HttpRequest&)>;

    struct RequestHandlingPair{
        HandlerMatcher matcher;
        RequestHandler handler;
    };

    class Container{
    public:
        Container() = default;

        Container(const std::vector<RequestHandlingPair>& container) : container_(container) {}

        Container(const Container& container) : container_(container.GetContainer()) {}

        void AddValues(const std::vector<RequestHandlingPair>& container){
            for (const RequestHandlingPair& pair : container){
                container_.push_back(pair);
            }
        }

        void AddValues(const Container& container){
            AddValues(container.GetContainer());
        }

        std::vector<RequestHandlingPair> GetContainer() const {
            return container_;
        }

    private:
        std::vector<RequestHandlingPair> container_;
    };

    class RouterBase {
    public:
        RouterBase(const Container& route_map) : route_map_(route_map) {}

        RequestHandler GetRequestHandler(const HttpRequest& request) const {
            RequestHandler* founded_handler = nullptr;
            for (auto [matcher, handler] : route_map_.GetContainer()){
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
