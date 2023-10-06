#pragma once

#include "WebHandler.hpp"

namespace web_layout{

    HttpResponse WebHandler::HandleRequest(const HttpRequest& http_request) {
        return HttpResponse(Method::GET, "", "", "");
    }

} // namespace web_layout
