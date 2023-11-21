#pragma once

#include <variant>
#include <vector>
#include <queue>
#include <mutex>
#include <string>

#include "DatabaseController.hpp"

namespace database{
    template<typename Connection, typename Controller, typename Store>
    class Database{
    public:
        Database(const std::string& db_name_){
            for(int i = 0; i < MAX_CONNECTIONS; ++i){
                connections_.push(Connection(db_name_));
            }
        }

        std::vector<Store> HandleQuery(const std::string& query, const std::vector<Store>& parameters){
            mutex_.lock();
            Connection connection = connections_.front();
            connections_.pop();

            std::vector<Store> result = controller_.HandleQuery(connection, query, parameters);

            connections_.push(connection);
            mutex_.unlock();

            return result;
        }

    private:
        const int MAX_CONNECTIONS = 10;
        std::queue<Connection> connections_;
        std::mutex mutex_;
        Controller controller_;
    };
}