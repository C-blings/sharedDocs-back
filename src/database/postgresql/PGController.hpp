#pragma once

#include <cassert>
#include <exception>
#include <pqxx/except.hxx>
#include <pqxx/prepared_statement.hxx>
#include <pqxx/transaction.hxx>
#include <sstream>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>

#include <logging/Logger.hpp>
#include <database/postgresql/PGConnection.hpp>
#include <database/DatabaseController.hpp>

namespace database::postgresql{
    using Store = std::variant<int, bool, std::string>;

    struct VisitStore {
        std::vector<std::string> parameters;
        void operator()(const int& arg)         { parameters.emplace_back(std::to_string(arg)); }
        void operator()(const bool& arg)        { parameters.emplace_back(arg ? "true" : "false"); }
        void operator()(const std::string& arg) { parameters.emplace_back(arg); }
    };

    class PGController : public DatabaseController<PGConnection, Store>{
    public:
        std::vector<std::vector<Store>> HandleQuery(PGConnection& connection,
                                       const std::string& query, const std::vector<Store>& raw_parameters) override {
            std::vector<std::vector<Store>> result;

            try {
                pqxx::work worker{*connection.GetConnection()};

                VisitStore visitor;

                for(const auto& raw_parameter: raw_parameters) {
                    std::visit( visitor, raw_parameter);
                }

                std::vector<std::string> parameters = visitor.parameters; 
            
                pqxx::result raw_result = worker.exec_params(query, pqxx::prepare::make_dynamic_params(parameters));

                for(const auto &row: raw_result) {
                    result.emplace_back();
                    for(const auto &field: row) {
                        result.back().emplace_back(field.c_str());
                    }
                }

                worker.commit();
            } catch(pqxx::sql_error& error) {
                Logger(Error).Print("Database error: ", error.what(), "\n Query: ", error.query());
                throw error;
            } catch(std::exception& error) {
                Logger(Error).Print(error.what());
                throw error;
            }

            return result;
        }
    };
}

