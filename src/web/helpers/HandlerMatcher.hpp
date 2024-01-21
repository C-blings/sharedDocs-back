#pragma once

#include <regex>

#include <web/models/HttpRequest.hpp>
#include <iostream>

namespace web_layout{
    class HandlerMatcher{
    public:
        HandlerMatcher(Method method, const std::string& expression_to_match) :
                      method_(method), expression_to_match_(expression_to_match){
            str_ = expression_to_match;
        }

        // match request path with regex in handlers
        bool Match(const HttpRequest& request) const;

    private:
        Method method_;
        std::regex expression_to_match_;
        std::string str_;
    };
}

 