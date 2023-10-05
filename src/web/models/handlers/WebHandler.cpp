#pragma once

#include "WebHandler.hpp"

namespace web_layout{

    char* WebHandler::HandleRequest(const HttpRequest& http_request) {
        return "answer";
    }

} // namespace web_layout
