#include <gtest/gtest.h>
#include <pqxx/connection>
#include <string>
#include <variant>
#include <vector>
#include <database/postgresql/PGConnection.hpp>
#include <database/postgresql/PGController.hpp>
#include <file_helpers/FileReader.hpp>
#include <formats/json/Json.hpp>

using Store = std::variant<int, bool, std::string>;
static std::string database_name = "unknown";

TEST(InitializeValues, Initializing){
    file_helpers::FileReader file_reader("configs/database_config.json");
    std::string text = file_reader.GetFileText();
    formats::json::JsonValue config(text);
    database_name = config.GetValue<std::string>("databaseName");
}

TEST(PGControllerTestCreateTable, CheckParserResult) {
    const std::string request = "CREATE TABLE test ( \
        ID int, \
        LastName varchar(255), \
        FirstName varchar(255) \
        );";

    std::vector<Store> store;

    database::postgresql::PGConnection connection("shareDocs");

    database::postgresql::PGController controller;

    std::vector<std::vector<Store>> result = controller.HandleQuery(connection, request, store);


    EXPECT_FALSE(!result.empty());
}

TEST(PGControllerTestInsert, CheckParserResult) {
    const std::string request = "INSERT INTO test(ID, LastName, FirstName) VALUES($1, $2, $3)";

    std::vector<std::variant<int, bool, std::string>> store = {0, "Petr", "Petrovich"};

    database::postgresql::PGConnection connection("shareDocs");

    database::postgresql::PGController controller;

    std::vector<std::vector<Store>> result = controller.HandleQuery(connection, request, store);


    EXPECT_FALSE(!result.empty());
}

TEST(PGControllerTestSelect, CheckParserResult) {
    const std::string request = "SELECT * FROM test";

    std::vector<std::variant<int, bool, std::string>> store;

    database::postgresql::PGConnection connection("shareDocs");

    database::postgresql::PGController controller;

    std::vector<std::vector<Store>> result = controller.HandleQuery(connection, request, store);


    EXPECT_EQ(result.size(), 1);
}

TEST(PGControllerTestDropTable, CheckParserResult) {
    const std::string request = "DROP TABLE test";

    std::vector<std::variant<int, bool, std::string>> store;

    database::postgresql::PGConnection connection("shareDocs");

    database::postgresql::PGController controller;

    std::vector<std::vector<Store>> result = controller.HandleQuery(connection, request, store);

    EXPECT_FALSE(!result.empty());
}
