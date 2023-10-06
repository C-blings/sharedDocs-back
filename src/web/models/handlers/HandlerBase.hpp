#pragma once

#include "../HttpRequest.hpp"
#include "../HttpResponse.hpp"

namespace web_layout{

    class HandlerBase{
        public:

            virtual HttpResponse HandleRequest(const HttpRequest& http_request) = 0;
        
    };

} // namespace web_layout