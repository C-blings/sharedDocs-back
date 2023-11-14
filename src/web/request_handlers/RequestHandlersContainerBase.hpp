#pragma once

#include <map>
#include <functional>
#include "../models/HttpResponse.hpp"
#include "../models/HttpRequest.hpp"
#include "../helpers/HandlerMatcher.hpp"
#include "../models/routers/RouterBase.hpp"

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

