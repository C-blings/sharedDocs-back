#pragma once

#include "../HttpRequest.hpp"

namespace web_layout{

    class HandlerBase{
        public:

            virtual char* HandleRequest(const HttpRequest& http_request) = 0;
        
    };

} // namespace web_layout