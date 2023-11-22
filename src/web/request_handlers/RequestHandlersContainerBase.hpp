#pragma once

#include <map>
#include <functional>

#include <web/models/HttpResponse.hpp>
#include <web/models/HttpRequest.hpp>
#include <web/helpers/HandlerMatcher.hpp>
#include <web/models/routers/RouterBase.hpp>

namespace web_layout{
    class RequestHandlersContainerBase {
    public:
        RequestHandlersContainerBase() = default;

        Container GetContainer() const {
            return container_;
        }

        void SetContainer(Container container){
            container_ = container;
        }

    protected:
        Container container_;
    };
}

