#pragma once
#define FMT_HEADER_ONLY

#include <pqxx/pqxx>
#include <fmt/format.h>

#include "../DatabaseConnection.hpp"

namespace database::postgresql{
    class PGConnection : public DatabaseConnection<pqxx::connection> {
    public:
        PGConnection(const std::string db_name){
            std::string connection_string = FormatConnectionString(db_name).c_str();
            connection_ = std::make_shared<pqxx::connection>(connection_string);
        }

        std::shared_ptr<pqxx::connection> GetConnection() const override{
            return connection_;
        };
    private:
        std::string FormatConnectionString(const std::string& db_name){
            return fmt::format("host={} user={} password={} dbname={}", db_host_, db_user_, db_password_, db_name);
        }

    private:
        const std::string db_host_ = "localhost";
        const std::string db_user_ = "root";
        const std::string db_password_ = "1234";
    };
}
