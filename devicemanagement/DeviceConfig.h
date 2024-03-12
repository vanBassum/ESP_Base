#pragma once
#include "helpers.h"

class IDeviceConfig
{
public:
    virtual ~IDeviceConfig() {}
    virtual Result getProperty(const char *key, const char **value) = 0;
    virtual Result getProperty(const char *key, uint8_t *value) = 0;
    virtual Result getProperty(const char *key, uint16_t *value) = 0;
    virtual Result getProperty(const char *key, uint32_t *value) = 0;
    virtual Result getProperty(const char *key, int8_t *value) = 0;
    virtual Result getProperty(const char *key, int16_t *value) = 0;
    virtual Result getProperty(const char *key, int32_t *value) = 0;
    virtual Result getProperty(const char *key, int *value) = 0;
};

class DeviceConfigReader : public IDeviceConfig
{
    constexpr static const char* TAG = "DeviceConfigReader";
    Device deviceConfig;

    // Method to read properties of a device by key
    const DevicePropertyValue *getProperty(const char *key)
    {
        for (int i = 0; deviceConfig[i].key != nullptr; i++)
        {
            if (std::strcmp(deviceConfig[i].key, key) == 0)
            {
                return &deviceConfig[i].value;
            }
        }
        //ESP_LOGW(TAG, "Property for key '%s' not found", key);
        return nullptr; // Property not found
    }

public:
    // Constructor to initialize the device tree
    DeviceConfigReader(Device deviceConfig) : deviceConfig(deviceConfig) {}

    virtual Result getProperty(const char *key, const char **value) override
    {
        const DevicePropertyValue *v = getProperty(key);
        if (v == nullptr)
            return Result::Error;
        *value = v->str;
        return Result::Ok;
    }

    virtual Result getProperty(const char *key, uint8_t *value) override
    {
        const DevicePropertyValue *v = getProperty(key);
        if (v == nullptr)
            return Result::Error;
        *value = v->u08;
        return Result::Ok;
    }

    virtual Result getProperty(const char *key, uint16_t *value) override
    {
        const DevicePropertyValue *v = getProperty(key);
        if (v == nullptr)
            return Result::Error;
        *value = v->u16;
        return Result::Ok;
    }

    virtual Result getProperty(const char *key, uint32_t *value) override
    {
        const DevicePropertyValue *v = getProperty(key);
        if (v == nullptr)
            return Result::Error;
        *value = v->u32;
        return Result::Ok;
    }

    virtual Result getProperty(const char *key, int8_t *value) override
    {
        const DevicePropertyValue *v = getProperty(key);
        if (v == nullptr)
            return Result::Error;
        *value = v->i08;
        return Result::Ok;
    }

    virtual Result getProperty(const char *key, int16_t *value) override
    {
        const DevicePropertyValue *v = getProperty(key);
        if (v == nullptr)
            return Result::Error;
        *value = v->i16;
        return Result::Ok;
    }

    virtual Result getProperty(const char *key, int32_t *value) override
    {
        const DevicePropertyValue *v = getProperty(key);
        if (v == nullptr)
            return Result::Error;
        *value = v->i32;
        return Result::Ok;
    }

    virtual Result getProperty(const char *key, int *value) override
    {
        const DevicePropertyValue *v = getProperty(key);
        if (v == nullptr)
            return Result::Error;
        *value = v->i32;
        return Result::Ok;
    }
};
