#pragma once
#include <string>
#include "helpers.h"

class Config;
class IConfig
{
    constexpr static const char* TAG = "IConfig";
public:
    std::string _key;

    virtual Config operator[](const std::string& key);
    virtual Result Add(std::shared_ptr<IConfig> value)  { ESP_LOGE(TAG, "Not supported"); return Result::Error; }
    virtual Result Populate(std::string& value)         { ESP_LOGE(TAG, "Not supported"); return Result::Error; }
    virtual Result Set(const std::string& value)        { ESP_LOGE(TAG, "Not supported"); return Result::Error; }
};

