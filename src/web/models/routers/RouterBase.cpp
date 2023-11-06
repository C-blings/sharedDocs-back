#include "RouterBase.hpp"
#include <optional>

namespace web_layout{
    RequestHandler RouterBase::GetRequestHandler(const HttpRequest& request) const {
        std::optional<RequestHandler> founded_handler;
        for (auto [matcher, handler] : route_map_.GetContainer()){
            if(matcher.Match(request)){
                founded_handler = handler;
                break;
            }
        }

        if (!founded_handler.has_value()){
            throw std::runtime_error("No handler founded ");
        }else{
            return founded_handler.value();
        }
    };

    void Container::AddValues(const std::vector<RequestHandlingPair>& container){
        for (const RequestHandlingPair& pair : container){
            container_.push_back(pair);
        }
    }
}