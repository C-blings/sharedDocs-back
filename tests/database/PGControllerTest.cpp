#include <gtest/gtest.h>
#include <pqxx/connection.hxx>
#include <string>
#include <variant>
#include <vector>
#include <database/postgresql/PGConnection.hpp>
#include <database/postgresql/PGController.hpp>

TEST(PGControllerTestCreateTable, CheckParserResult) {
    const std::string request = "CREATE TABLE Test ( \
        ID int, \
        LastName varchar(255), \
        FirstName varchar(255) \
        );";
    
    std::vector<std::variant<int, bool, std::string>> store;

    database::postgresql::PGConnection connection("tmp");

    database::postgresql::PGController controller;

    std::vector<std::vector<std::variant<int, bool, std::string>>> result = controller.HandleQuery(connection, request, store);


    EXPECT_FALSE(!result.empty());
}

TEST(PGControllerTestInsert, CheckParserResult) {
    const std::string request = "INSERT INTO test(ID, LastName, FirstName) VALUES($1, $2, $3)";
    
    std::vector<std::variant<int, bool, std::string>> store = {0, "Petr", "Petrovich"};

    database::postgresql::PGConnection connection("tmp");

    database::postgresql::PGController controller;

    std::vector<std::vector<std::variant<int, bool, std::string>>> result = controller.HandleQuery(connection, request, store);


    EXPECT_FALSE(!result.empty());
}

TEST(PGControllerTestSelect, CheckParserResult) {
    const std::string request = "SELECT * FROM Test";
    
    std::vector<std::variant<int, bool, std::string>> store;

    database::postgresql::PGConnection connection("tmp");

    database::postgresql::PGController controller;

    std::vector<std::vector<std::variant<int, bool, std::string>>> result = controller.HandleQuery(connection, request, store);


    EXPECT_EQ(result.size(), 1);
}

TEST(PGControllerTestDropTable, CheckParserResult) {
    const std::string request = "DROP TABLE Test";
    
    std::vector<std::variant<int, bool, std::string>> store;

    database::postgresql::PGConnection connection("tmp");

    database::postgresql::PGController controller;

    std::vector<std::vector<std::variant<int, bool, std::string>>> result = controller.HandleQuery(connection, request, store);


    EXPECT_FALSE(!result.empty());
}
