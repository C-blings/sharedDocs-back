#pragma once

#include "../models/HttpRequest.hpp"
#include <regex>

namespace web_layout{
    class HandlerMatcher{
    public:
        HandlerMatcher(Method method, std::regex expression_to_match) :
                      method_(method), expression_to_match_(expression_to_match){}

        // match request path with regex in handlers
        bool Match(const HttpRequest& request) const;

    private:
        Method method_;
        std::regex expression_to_match_;
    };
}

 