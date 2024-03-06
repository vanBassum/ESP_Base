#pragma once
#include <string_view>
#include <any>
#include "helpers.h"
#include "nvs_flash.h"


class IConfigProvider {
public:
    class Proxy {
        std::shared_ptr<IConfigProvider> provider;
    public:
        Proxy(std::shared_ptr<IConfigProvider> provider) : provider(provider){}

        Proxy operator[](const std::string& subkey) { return provider->GetProxy(subkey); }

        template<typename T>
        Result Get(T value) { return provider->Get(value); }

        template<typename T>
        Result Set(const T value) { return provider->Set(value); }
    };

    Proxy operator[](const std::string& key) { return GetProxy(key); }

    virtual Result Get(int8_t* value)                           { ESP_LOGE("IConfigProvider", "Not implemented get for type 'int8_t'"); return Result::NotSupported; }
    virtual Result Get(int16_t* value)                          { ESP_LOGE("IConfigProvider", "Not implemented get for type 'int16_t'"); return Result::NotSupported; }
    virtual Result Get(int32_t* value)                          { ESP_LOGE("IConfigProvider", "Not implemented get for type 'int32_t'"); return Result::NotSupported; }
    virtual Result Get(int64_t* value)                          { ESP_LOGE("IConfigProvider", "Not implemented get for type 'int64_t'"); return Result::NotSupported; }
    virtual Result Get(uint8_t* value)                          { ESP_LOGE("IConfigProvider", "Not implemented get for type 'uint8_t'"); return Result::NotSupported; }
    virtual Result Get(uint16_t* value)                         { ESP_LOGE("IConfigProvider", "Not implemented get for type 'uint16_t'"); return Result::NotSupported; }
    virtual Result Get(uint32_t* value)                         { ESP_LOGE("IConfigProvider", "Not implemented get for type 'uint32_t'"); return Result::NotSupported; }
    virtual Result Get(uint64_t* value)                         { ESP_LOGE("IConfigProvider", "Not implemented get for type 'uint64_t'"); return Result::NotSupported; }
    virtual Result Get(std::string* value)                      { ESP_LOGE("IConfigProvider", "Not implemented get for type 'std::string_view'"); return Result::NotSupported; }

    virtual Result Set(const int8_t value)                      { ESP_LOGE("IConfigProvider", "Not implemented set for type 'int8_t'"); return Result::NotSupported; }
    virtual Result Set(const int16_t value)                     { ESP_LOGE("IConfigProvider", "Not implemented set for type 'int16_t'"); return Result::NotSupported; }
    virtual Result Set(const int32_t value)                     { ESP_LOGE("IConfigProvider", "Not implemented set for type 'int32_t'"); return Result::NotSupported; }
    virtual Result Set(const int64_t value)                     { ESP_LOGE("IConfigProvider", "Not implemented set for type 'int64_t'"); return Result::NotSupported; }
    virtual Result Set(const uint8_t value)                     { ESP_LOGE("IConfigProvider", "Not implemented set for type 'uint8_t'"); return Result::NotSupported; }
    virtual Result Set(const uint16_t value)                    { ESP_LOGE("IConfigProvider", "Not implemented set for type 'uint16_t'"); return Result::NotSupported; }
    virtual Result Set(const uint32_t value)                    { ESP_LOGE("IConfigProvider", "Not implemented set for type 'uint32_t'"); return Result::NotSupported; }
    virtual Result Set(const uint64_t value)                    { ESP_LOGE("IConfigProvider", "Not implemented set for type 'uint64_t'"); return Result::NotSupported; }
    virtual Result Set(const std::string value)                 { ESP_LOGE("IConfigProvider", "Not implemented set for type 'std::string_view'"); return Result::NotSupported; }

protected:
    virtual Proxy GetProxy(const std::string& key) = 0;
};



