#pragma once

#include <exception>
#include <sstream>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>

#include <logging/Logger.hpp>
#include <database/postgresql/PGConnection.hpp>
#include <database/DatabaseController.hpp>
#include <pqxx/transaction>
#include <pqxx/result>

namespace database::postgresql{
    using Store = std::variant<int, bool, std::string>;

    class GetVariantValue{
    private:
        static std::string value_;

    public:
        static std::string GetValue(Store variant){
            std::visit(VisitStore{}, variant);
            return value_;
        }

    private:
        struct VisitStore {
            void operator()(int arg) { value_ = std::to_string(arg); }
            void operator()(bool arg) { value_ = (arg ? "true" : "false"); }
            void operator()(const std::string& arg) { value_ = arg; }
        };
    };


    class PGController : public DatabaseController<PGConnection, Store>{
    public:
        std::vector<std::vector<Store>> HandleQuery(PGConnection& connection,
                                       const std::string& query, const std::vector<Store>& raw_parameters) override {
            std::vector<std::vector<Store>> result;

            try {
                pqxx::work worker{*connection.GetConnection()};

                pqxx::params parameters;

                for(const auto& raw_parameter: raw_parameters) {
                    std::string value = GetVariantValue::GetValue(raw_parameter);
                    parameters.append(value);
                }

                pqxx::result raw_result = worker.exec_params(query, parameters);

                for(const auto& row : raw_result) {
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

