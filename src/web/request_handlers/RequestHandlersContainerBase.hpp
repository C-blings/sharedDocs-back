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
        RequestHandlersContainerBase(const Container& container) noexcept : container_(container) {}

        Container GetContainer() const {
            return container_;
        }

    protected:
        Container container_;
    };
}

