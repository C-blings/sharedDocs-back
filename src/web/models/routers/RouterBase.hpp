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

        void AddValues(const std::vector<RequestHandlingPair>& container);

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

        // find request handler
        RequestHandler GetRequestHandler(const HttpRequest& request) const;

    private:
        const Container route_map_;
    };
}
