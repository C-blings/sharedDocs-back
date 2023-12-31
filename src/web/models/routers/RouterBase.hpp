#pragma once

#include <map>
#include <functional>

#include <web/models/HttpRequest.hpp>
#include <web/models/HttpResponse.hpp>
#include <web/helpers/HandlerMatcher.hpp>


namespace web_layout{
    using RequestHandler = std::function<HttpResponse (const HttpRequest&)>;

    // pair of matcher and function, which will handler request
    struct RequestHandlingPair{
        HandlerMatcher matcher;
        RequestHandler handler;
    };


    // class for storing containers
    class Container{
    public:
        Container() = default;

        Container(const std::vector<RequestHandlingPair>& container) : container_(container) {}

        Container(const Container& container) : container_(container.GetContainer()) {}

        void AddValues(const std::vector<RequestHandlingPair>& container);

        void AddValue(const RequestHandlingPair& handling_pair);

        void AddValues(const Container& container){
            AddValues(container.GetContainer());
        }

        std::vector<RequestHandlingPair> GetContainer() const {
            return container_;
        }

    private:
        std::vector<RequestHandlingPair> container_;
    };

    // class which holds all RequestHandlingPairs
    class RouterBase {
    public:
        RouterBase(const Container& route_map) : route_map_(route_map) {}

        // find request handler
        RequestHandler GetRequestHandler(const HttpRequest& request) const;

    private:
        const Container route_map_;
    };
}
