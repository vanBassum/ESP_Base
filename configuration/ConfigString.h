#pragma once
#include "IConfig.h"



class ConfigString : public IConfig
{
    static constexpr inline const char* TAG = "ConfigString";
    std::string _value;
public:
    ConfigString(const std::string& key)
    {
        _key = key;
    }

    Result Populate(std::string& value) override
    {
        value = _value;
        return Result::Ok;
    }

    Result Set(const std::string& value)override
    {
        _value = value;
        return Result::Ok;
    }

    Result Set(const char* value)override
    {
        _value = std::string(value);
        return Result::Ok;
    }
};

