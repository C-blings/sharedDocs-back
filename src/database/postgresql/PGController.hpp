#pragma once

#include "PGConnection.hpp"
#include "../DatabaseController.hpp"

namespace database::postgresql{
    using Store = std::variant<int, bool, std::string>;

    class PGController : public DatabaseController<PGConnection, Store>{
    public:
        std::vector<Store> HandleQuery(PGConnection& connection,
                                       const std::string& query, const std::vector<Store>& parameters) override {
            return {};
        }
    };
}

