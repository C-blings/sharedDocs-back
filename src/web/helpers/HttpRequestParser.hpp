#pragma once

#include "../models/HttpRequest.hpp"
#include <sstream>
#include <vector>
#include <boost/algorithm/string.hpp>

namespace web_layout{

    class HttpRequestParser{
        public:
            
            static HttpRequest GetHttpRequest(const std::string& request){
                std::vector<std::string> request_lines;
                boost::split(request_lines, request, boost::is_any_of("\n\r"), boost::token_compress_on);

                return HttpRequest(Method::GET, "", "", "");
            }

    };

} // namespace web_layout