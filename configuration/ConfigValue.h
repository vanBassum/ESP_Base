#pragma once
#include "IConfig.h"
#include <string>

template<typename T>
class ConfigValue : public IConfig
{
    static constexpr inline const char *TAG = "ConfigValue";
    T _value;
public:

    ConfigValue(const std::string &key)
    {
        _key = key;
    }


    ConfigTypes GetType() override {
        if constexpr (std::is_same_v<T, std::string>) return ConfigTypes::String;
        if constexpr (std::is_same_v<T, std::int8_t>) return ConfigTypes::INT8;
        if constexpr (std::is_same_v<T, std::uint8_t>) return ConfigTypes::UINT8;
        if constexpr (std::is_same_v<T, std::int16_t>) return ConfigTypes::INT16;
        if constexpr (std::is_same_v<T, std::uint16_t>) return ConfigTypes::UINT16;
        if constexpr (std::is_same_v<T, std::int32_t>) return ConfigTypes::INT32;
        if constexpr (std::is_same_v<T, std::uint32_t>) return ConfigTypes::UINT32;
        if constexpr (std::is_same_v<T, std::int64_t>) return ConfigTypes::INT64;
        if constexpr (std::is_same_v<T, std::uint64_t>) return ConfigTypes::UINT64;
        if constexpr (std::is_same_v<T, bool>) return ConfigTypes::BOOL;
        if constexpr (std::is_same_v<T, float>) return ConfigTypes::FLOAT;
        if constexpr (std::is_same_v<T, double>) return ConfigTypes::DOUBLE;
        if constexpr (std::is_same_v<T, long double>) return ConfigTypes::LONG_DOUBLE;

        return ConfigTypes::Unknown;
    }


    Result Populate(T &value) override
    {
        value = _value;
        return Result::Ok;
    }

    Result Set(const T &value) override
    {
        _value = value;
        return Result::Ok;
    }

    void Print(int depth) override
    {
        std::string indentation(depth * 2, ' '); // Create indentation string with depth * 2 spaces

        if constexpr (std::is_same_v<T, char*>)
            printf("%s%s: %s\n", indentation.c_str(), _key.c_str(), _value);
        else if constexpr (std::is_same_v<T, std::string>)
            printf("%s%s: %s\n", indentation.c_str(), _key.c_str(), _value.c_str());
        else
            printf("%s%s: %s\n", indentation.c_str(), _key.c_str(), std::to_string(_value).c_str());

    }
};
