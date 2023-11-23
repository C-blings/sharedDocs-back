#include "WebServer.hpp"

namespace web_layout{
    HttpResponse WebServer::HandleRequest(const HttpRequest& request) const {
        RequestHandler handler;

        try{
            handler = router_.GetRequestHandler(request);
        }catch (std::exception& e){
            return HttpResponse(404, "Page not found", {{"Cache-Control", "no-cache, private"}, {"Content-Type", "text/html"}}, "Ooops, no page found");
        }

        return handler(request);
    }
} // namespace web_layout
