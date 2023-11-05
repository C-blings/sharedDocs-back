#pragma once

#include <string>
#include <unordered_map>

namespace web_layout{
    enum Method{
        GET,
        POST,
        PUT,
        DELETE,
        OPTIONS
    };

    class HttpRequest{
    public:
        HttpRequest(Method method, const std::string& path,
                    const std::unordered_map<std::string,std::string>& headers_, const std::string& body) :
                method_(method), path_(path),
                headers_(headers_), body_(body) {}

        Method GetMethod() const { return method_; }

        std::string GetPath() const { return path_; }

    private:
        const Method method_;
        const std::string path_;
        const std::unordered_map<std::string,std::string> headers_;
        const std::string body_;
    };
} // namespace web_layout
