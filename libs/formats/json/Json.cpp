#include "Json.hpp"

namespace formats::json{
    JsonValue::JsonValue(const std::string& text){
        Json::Reader reader;
        reader.parse(text, value_);
    }
}