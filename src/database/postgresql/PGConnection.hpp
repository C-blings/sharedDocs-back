#pragma once
#define FMT_HEADER_ONLY

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

        ~PGConnection(){
            connection_->close();
        }
    private:
        std::string FormatConnectionString(const std::string& db_name){
            return fmt::format("host={} user={} password={} dbname={}", db_host_, db_user_, db_password_, db_name);
        }

    private:
        const std::string db_host_ = "172.28.0.3";
        const std::string db_user_ = "postgres";
        const std::string db_password_ = "123";
    };
}
