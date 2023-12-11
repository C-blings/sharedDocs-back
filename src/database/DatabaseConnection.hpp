#pragma once

#include <memory>

namespace database{
    template<typename T>
    class DatabaseConnection{
    public:
       virtual std::shared_ptr<T> GetConnection() const = 0;

    protected:
        std::shared_ptr<pqxx::connection> connection_;
    };
}
