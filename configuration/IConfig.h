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
    virtual Result Set(const char* value)               { ESP_LOGE(TAG, "Not supported"); return Result::Error; }

    virtual Result Populate(int8_t& value)              { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Populate(uint8_t& value)             { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Populate(int16_t& value)             { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Populate(uint16_t& value)            { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Populate(int32_t& value)             { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Populate(uint32_t& value)            { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Populate(int64_t& value)             { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Populate(uint64_t& value)            { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Populate(bool& value)                { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Populate(float& value)               { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Populate(double& value)              { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Populate(long double& value)         { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Set(const int8_t& value)             { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Set(const uint8_t& value)            { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Set(const int16_t& value)            { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Set(const uint16_t& value)           { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Set(const int32_t& value)            { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Set(const uint32_t& value)           { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Set(const int64_t& value)            { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Set(const uint64_t& value)           { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Set(const bool& value)               { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Set(const float& value)              { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Set(const double& value)             { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Set(const long double& value)        { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }


};
