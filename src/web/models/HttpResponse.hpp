#pragma once

#include <string>
#include <sstream>
#include <unordered_map>

namespace web_layout{

    class HttpResponse{
    public:
        HttpResponse() : status_code_(404){}

        explicit HttpResponse(int status_code, const std::string& result_test,
                              const std::unordered_map<std::string, std::string>& headers,
                              const std::string& body) :
                              status_code_(status_code), result_text_(result_test),
                              headers_(headers), body_(body) {}

        HttpResponse(const HttpResponse& response) :
                status_code_(response.status_code_), result_text_(response.result_text_),
                headers_(response.headers_), body_(response.body_){}

        HttpResponse operator=(const HttpResponse& response) {
            return HttpResponse(response);
        }

        std::string AsString() const {
            std::stringstream string_stream;
            string_stream << "HTTP/1.1 " << status_code_ << " " << result_text_ << "\r\n";
            for (auto [header, value] : headers_){
                string_stream << header << ": " << value << "\r\n";
            }
            string_stream << "Cache-Control: no-cache, private\r\n";
            string_stream << "Content-Type: text/html\r\n";
            string_stream << "Content-Length: " << body_.size() << "\r\n";
            string_stream << "\r\n";
            string_stream << body_;

            return string_stream.str();
        }

    private:
        const int status_code_;
        const std::string result_text_;
        const std::unordered_map<std::string, std::string> headers_;
        const std::string body_;
    };
} // namespace web_layout