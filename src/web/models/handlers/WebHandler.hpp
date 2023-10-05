#pragma once

#include "HandlerBase.hpp"

namespace web_layout{

    class WebHandler : public HandlerBase{
        public:
            char* HandleRequest(const HttpRequest& http_request) override;
        
    };

} // namespace web_layout