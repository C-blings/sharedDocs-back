#include "HttpResponse.hpp"

namespace web_layout{
    std::string HttpResponse::AsString() const {
        std::stringstream string_stream;
        string_stream << "HTTP/1.1 " << status_code_ << " " << result_text_ << "\r\n";
        for (auto [header, value] : headers_){
            string_stream << header << ": " << value << "\r\n";
        }
        string_stream << "Cache-Control: no-cache, private\r\n";
        string_stream << "Content-Type: text/html\r\n";
        if (body_.has_value()){
            string_stream << "Content-Length: " << body_->size() << "\r\n";
            string_stream << "\r\n";
            string_stream << body_.value();
        }else{
            string_stream << "\r\n";
        }


        return string_stream.str();
    }
}