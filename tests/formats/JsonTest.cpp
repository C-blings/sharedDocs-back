#include <gtest/gtest.h>
#include <jsoncpp/json/json.h>
#include <formats/json/Json.hpp>

TEST(CheckAllFields, JsonTest){
    using JsonValue = formats::json::JsonValue;

    const std::string input_value("{"
                        "\"host\": \"127.0.0.1\","
                        "\"port\": 80,"
                        "\"object\": {"
                        "\"value\": \"string\""
                        "}}");

    const std::string host("127.0.0.1");
    const int port = 80;
    const std::string value("string");
    
    JsonValue json(input_value);
    EXPECT_EQ(json.GetValue<int>("port"), port);
    EXPECT_EQ(json.GetValue<std::string>("host"), host);
    JsonValue object = json.GetValue<JsonValue>("object");
    EXPECT_EQ(object.GetValue<std::string>("value"), value);
}
