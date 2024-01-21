#include <iostream>
#include "HandlerMatcher.hpp"

namespace web_layout{

    // checks if regex of matcher is equal of request path and methods equal
    bool HandlerMatcher::Match(const HttpRequest& request) const{
        std::smatch regex_match;
        bool regex_match_success = false;
        std::string request_path = request.GetPath();

        if (std::regex_search(request_path, regex_match, expression_to_match_)) {
            std::string match_result = regex_match.str();

            regex_match_success = !match_result.empty() && request_path.size() == match_result.size();
        }

        return method_ == request.GetMethod() && regex_match_success;
    }
}

 