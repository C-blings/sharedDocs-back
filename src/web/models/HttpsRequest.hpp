#pragma once

#include <string>

namespace web_layout{

    enum Method{
        GET, 
        POST,
    };


    class HttpRequest{
        public:
            HttpRequest(Method method, const std::string& path) :
                        method_(method), path_(path) {}

        private:
            const Method method_;
            const std::string path_; 
    };

} // namespace web_layout