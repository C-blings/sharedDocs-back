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

<<<<<<< HEAD
        std::vector<std::vector<Store>> HandleQuery(const std::string& query, const std::vector<Store>& parameters) {
=======
        std::vector<Store> HandleQuery(const std::string& query, const std::vector<Store>& parameters){
>>>>>>> 2a1300154042054268781c11227867e0572b8b37
            mutex_.lock();
            Connection connection = connections_.front();
            connections_.pop();

<<<<<<< HEAD
            std::vector<std::vector<Store>> result = controller_.HandleQuery(connection, query, parameters);
=======
            std::vector<Store> result = controller_.HandleQuery(connection, query, parameters);
>>>>>>> 2a1300154042054268781c11227867e0572b8b37

            connections_.push(connection);
            mutex_.unlock();

            return result;
        }

<<<<<<< HEAD
        ~Database() {
            while(!connections_.empty()) {
                Connection& connection = connections_.front();
                connections_.pop();

                connection.disconnect();
            }
        }

    private:
        static const int MAX_CONNECTIONS = 10;
=======
    private:
        const int MAX_CONNECTIONS = 10;
>>>>>>> 2a1300154042054268781c11227867e0572b8b37
        std::queue<Connection> connections_;
        std::mutex mutex_;
        Controller controller_;
    };
<<<<<<< HEAD
}
=======
}
>>>>>>> 2a1300154042054268781c11227867e0572b8b37
