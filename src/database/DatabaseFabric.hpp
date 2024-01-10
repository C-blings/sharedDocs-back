#pragma once

#include <memory>
#include <database/Database.hpp>
#include <database/postgresql/PGController.hpp>
#include <database/postgresql/PGConnection.hpp>

namespace database{
    using PGDatabase = database::Database<
            postgresql::PGConnection,
            postgresql::PGController,
            postgresql::Store>;

    class DatabaseFabric{
    public:

        static std::shared_ptr<PGDatabase> GetDatabase(){
            return database_;
        }

    private:
        static std::shared_ptr<PGDatabase> database_;
    };
}