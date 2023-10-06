#pragma once

#include "../models/HttpRequest.hpp"

namespace web_layout{

    class HttpRequestParser{
        public:
            
            static HttpRequest GetHttpRequest(char buf[], int size){
                return HttpRequest(Method::GET, "", "", "");
            }

    };

} // namespace web_layout