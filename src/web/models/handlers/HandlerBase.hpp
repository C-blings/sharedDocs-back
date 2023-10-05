#pragma once

#include "../HttpsRequest.hpp"

namespace web_layout{

    class HandlerBase{
        public:

            virtual void HandleRequest(const HttpRequest& http_request) = 0;
        
    };

} // namespace web_layout