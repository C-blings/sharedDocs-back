#pragma once

#include <memory>
#include <database/DatabaseFabric.hpp>
#include <web/request_handlers/RequestHandlersContainerBase.hpp>

namespace web_layout{

    class RegistrationContainers : public RequestHandlersContainerBase {
    public:
        RegistrationContainers();
    private:
        static HttpResponse AddUser(const HttpRequest& request);

    private:
        static std::shared_ptr<database::PGDatabase> database_;
    };
}
