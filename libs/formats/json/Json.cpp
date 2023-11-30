#include "Json.hpp"

#include <iostream>

namespace formats::json{
    JsonValue::JsonValue(const std::string& text){
        Json::Reader reader;
        reader.parse(text, value_);
    }

    template<>
    int JsonValue::GetValue<int>(const std::string& key) {
        return value_[key].asInt();
    }

    template<>
    std::string JsonValue::GetValue<std::string>(const std::string& key) {
        return value_[key].asString();
    }

    template<>
    bool JsonValue::GetValue<bool>(const std::string& key) {
        return value_[key].asBool();
    }

    template<>
    long long JsonValue::GetValue<long long>(const std::string& key) {
        return value_[key].asInt64();
    }

    template<>
    double JsonValue::GetValue<double>(const std::string& key) {
        return value_[key].asDouble();
    }

    template<>
    JsonValue JsonValue::GetValue<JsonValue>(const std::string& key) {
        return JsonValue(value_[key]);
    }

}