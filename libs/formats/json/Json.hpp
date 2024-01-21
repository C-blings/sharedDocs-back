#pragma once

#define FMT_HEADER_ONLY

#include "jsoncpp/json/json.h"

#include <fmt/format.h>

namespace formats::json{
    class JsonValue{
    public:

        explicit JsonValue(const std::string& text = "");

        JsonValue(const Json::Value& value) : value_(value) {}

        Json::Value GetValue() const { return value_; }

        template<typename T>
        T GetValue(const std::string& key) {
            throw std::runtime_error(fmt::format("Can not cast to: {}", typeid(T).name()));
        }

        void AddValue(const std::string& key, const std::string& value);

        void AddValue(const std::string& key, const JsonValue& value);

        std::string AsString();

    private:
        Json::Value value_;
    };
}