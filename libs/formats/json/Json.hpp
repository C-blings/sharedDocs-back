#pragma once

#include "jsoncpp/json/json.h"

namespace formats::json{
    class JsonValue{
    public:
        JsonValue(const std::string& text);

        Json::Value GetValue() const { return value_; }

        std::string GetValue(const std::string& key) { return value_[key].asString(); }

    private:
        Json::Value value_;
    };
}