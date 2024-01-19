#pragma once

#include <string>
#include <unordered_map>
#include <optional>

namespace web_layout{
    enum Method{
        GET,
        POST,
        PUT,
        DELETE,
        OPTIONS
    };

    class HttpRequest{
        using OptionalMap = std::optional<std::unordered_map<std::string,std::string>>;
    public:
        HttpRequest(Method method, const std::string& path,
                    const OptionalMap& headers_, const std::string& body,
                    const OptionalMap& parameters = std::nullopt) :
                method_(method), path_(path),
                headers_(headers_), body_(body), parameters_(parameters) {}

        Method GetMethod() const { return method_; }

        std::string GetPath() const { return path_; }

        std::unordered_map<std::string,std::string> GetHeaders() const {
            if (headers_.has_value()){
                return headers_.value();
            }else{
                return {};
            }
        }

        std::unordered_map<std::string,std::string> GetParameters() const {
            if (parameters_.has_value()){
                return parameters_.value();
            }else{
                return {};
            }
        }

        std::string GetBody() const { return body_; }

    private:
        const Method method_;
        const std::string path_;
        const OptionalMap headers_;
        const OptionalMap parameters_;
        const std::string body_;
    };
} // namespace web_layout
