#pragma once

#include <vector>
#include <string>

namespace database{
    template<typename Connection, typename Store>
    class DatabaseController {
    public:
        virtual std::vector<Store> HandleQuery(Connection& connection,
                                       const std::string& query, const std::vector<Store>& parameters) = 0;
    };
}