#pragma once

#include <string>

namespace web_layout{
    enum Method{
        GET,
        POST,
    };


    class HttpRequest{
    public:
        HttpRequest(Method method, const std::string& path,
                    const std::string& headers_, const std::string& body) :
                method_(method), path_(path),
                headers_(headers_), body_(body) {}

    private:
        const Method method_;
        const std::string path_;
        const std::string headers_;
        const std::string body_;
    };
} // namespace web_layout