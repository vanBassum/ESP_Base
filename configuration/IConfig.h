#pragma once
#include <string>
#include "helpers.h"

enum class ConfigTypes{
    Unknown,
    Container,
    Factory,
    String,
    INT8,
    UINT8,
    INT16,
    UINT16,
    INT32,
    UINT32,
    INT64,
    UINT64,
    BOOL,
    FLOAT,
    DOUBLE,
    LONG_DOUBLE
};


class Config;
class IConfig
{
    constexpr static const char* TAG = "IConfig";
public:
    std::string _key;
    virtual ConfigTypes GetType() = 0;

    virtual Config operator[](const std::string& key);
    virtual Result Add(std::shared_ptr<IConfig> value)  { ESP_LOGE(TAG, "Not supported"); return Result::Error; }

    virtual Result Populate(std::string& value)         { ESP_LOGE(TAG, "Not supported"); return Result::Error; }
    virtual Result Populate(int8_t& value)              { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Populate(uint8_t& value)             { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Populate(int16_t& value)             { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Populate(uint16_t& value)            { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Populate(int32_t& value)             { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Populate(int& value)                 { return Populate((int32_t&)value); }
    virtual Result Populate(uint32_t& value)            { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Populate(int64_t& value)             { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Populate(uint64_t& value)            { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Populate(bool& value)                { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Populate(float& value)               { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Populate(double& value)              { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Populate(long double& value)         { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }

    virtual Result Set(const std::string& value)        { ESP_LOGE(TAG, "Not supported"); return Result::Error; }
    virtual Result Set(const char* value)               { return Set(std::string(value)); }
    virtual Result Set(const int8_t& value)             { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Set(const uint8_t& value)            { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Set(const int16_t& value)            { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Set(const uint16_t& value)           { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Set(const int32_t& value)            { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Set(const int& value)                { return Set((const int32_t&)value); }
    virtual Result Set(const uint32_t& value)           { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Set(const int64_t& value)            { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Set(const uint64_t& value)           { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Set(const bool& value)               { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Set(const float& value)              { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Set(const double& value)             { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }
    virtual Result Set(const long double& value)        { ESP_LOGE(TAG, "Type mismatch"); return Result::Error; }

    virtual void Print(int depth) {
        std::string indentation(depth * 2, ' '); // Create indentation string with depth * 4 spaces
        printf("%s%s: Not implemented\n", indentation.c_str(), _key.c_str());
    }
};

