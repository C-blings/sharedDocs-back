#pragma once

#include <web/request_handlers/RequestHandlersContainerBase.hpp>

namespace web_layout{
    class RegistrationContainers : public RequestHandlersContainerBase {
    public:
        RegistrationContainers();
    private:
        static HttpResponse AddUser(const HttpRequest& request);
    };
}
