#pragma once

#include "../HttpRequest.hpp"
#include <regex>

namespace web_layout{
    class HandlerMatcher{
    public:
        HandlerMatcher(Method method, const std::regex& expression_to_match) :
                      method_(method), expression_to_match_(expression_to_match){}

        bool Match(const HttpRequest& request) const{
            std::smatch regex_match;
            bool regex_match_success = false;
            std::string request_path = request.GetPath();
            if (std::regex_search(request_path, regex_match, expression_to_match_)){
                regex_match_success = regex_match.str().empty();
            }

            return method_ == request.GetMethod() && regex_match_success;
        }

    private:
        Method method_;
        std::regex expression_to_match_;
    };
}

 