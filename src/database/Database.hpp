#pragma once

#include <variant>
#include <vector>
#include <queue>
#include <mutex>
#include <string>

#include "DatabaseController.hpp"
#include <database/DatabaseConnection.hpp>
#include <database/DatabaseController.hpp>

namespace database{
    template<typename Connection, typename Controller, typename Store>
    class Database{
    public:
        explicit Database(const std::string& db_name_){
            for(int i = 0; i < kMaxConnections; ++i){
                connections_.push_back(std::make_unique<Connection>(db_name_));
            }
            connection_index_ = 0;
        }

        std::vector<std::vector<Store>> HandleQuery(const std::string& query, const std::vector<Store>& parameters) {
            mutex_.lock();
            Connection connection = *connections_[connection_index_];

            std::vector<std::vector<Store>> result = controller_.HandleQuery(connection, query, parameters);
            connection_index_ = (connection_index_ + 1) % kMaxConnections;
            mutex_.unlock();
            return result;
        }

    private:
        static const int kMaxConnections = 10;
        std::vector<std::unique_ptr<Connection>> connections_;
        int connection_index_;
        std::mutex mutex_;
        Controller controller_;
    };
}
