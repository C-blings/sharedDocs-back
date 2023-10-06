#pragma once

#include <string>
#include <sstream>

namespace web_layout{

    class HttpResponse{
    public:
        HttpResponse(Method method, const std::string& path,
                    const std::string& headers_, const std::string& body) :
                method_(method), path_(path),
                headers_(headers_), body_(body) {}

        std::string AsString() const {
            std::stringstream string_stream;
            std::string message = "Hello world!";
            string_stream << "HTTP/1.1 " << "200" << " OK\r\n";
            string_stream << "Cache-Control: no-cache, private\r\n";
            string_stream << "Content-Type: text/html\r\n";
            string_stream << "Content-Length: " << message.size() << "\r\n";
            string_stream << "\r\n";
            string_stream << message;

            return string_stream.str();
        }

    private:
        const Method method_;
        const std::string path_;
        const std::string headers_;
        const std::string body_;
    };
} // namespace web_layout