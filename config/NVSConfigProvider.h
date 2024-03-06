#pragma once
#include <string_view>
#include <any>
#include "helpers.h"
#include "nvs_flash.h"
#include "IConfigProvider.h"


class NVSConfigProvider : public IConfigProvider
{
public:
    class InternalNVSConfigProvider : public std::enable_shared_from_this<InternalNVSConfigProvider> {
        const std::string_view& partition;
        const std::string_view& nSpace;
        nvs_handle_t handle = NULL;
    public:

        class NVSConfigProviderItem : public IConfigProvider
        {
            std::shared_ptr<InternalNVSConfigProvider> parent;
            const std::string_view& key;
        public:
            NVSConfigProviderItem(std::shared_ptr<InternalNVSConfigProvider> parent, const std::string_view& key) : parent(parent), key(key) {  }
            ~NVSConfigProviderItem(){}

            virtual Result Get(uint8_t* value) override         { return nvs_get_u8(parent->handle, key.data(), value) == ESP_OK ? Result::Ok : Result::Error; }
            virtual Result Set(const uint8_t value) override    { return nvs_set_u8(parent->handle, key.data(), value) == ESP_OK ? Result::Ok : Result::Error; }

        protected:
            Proxy GetProxy(const std::string_view& key) override {
                assert(false);
            }
        };

        InternalNVSConfigProvider(const std::string_view& partition, const std::string_view& nSpace) : partition(partition), nSpace(nSpace)    {  }

        ~InternalNVSConfigProvider()
        {
            if(handle != NULL)
                nvs_close(handle);
        }

        Result Init()
        {
            //TODO: Prevent twice init! and what about mutexing?
            esp_err_t err = nvs_flash_init_partition(partition.data());
            if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
                ESP_ERROR_CHECK(nvs_flash_erase());
                err = nvs_flash_init_partition(partition.data());
            }

            if(err != ESP_OK)
                return Result::Error;
            
            err = nvs_open(nSpace.data(), NVS_READWRITE, &handle);
            return err == ESP_OK ? Result::Ok : Result::Error;
        }

        Result Commit()
        {
            if(handle == NULL)
                return Result::Error;
            esp_err_t err = nvs_commit(handle);
            return err == ESP_OK ? Result::Ok : Result::Error;
        }
    };

private:
    std::shared_ptr<InternalNVSConfigProvider> internal;

public:
    NVSConfigProvider(const std::string_view& partition, const std::string_view& nSpace)
    {
        internal = std::make_shared<InternalNVSConfigProvider>(partition, nSpace);
    }

    ~NVSConfigProvider(){}

    Result Init() { return internal->Init(); }

    Result Commit() { return internal->Commit(); }


protected:
    Proxy GetProxy(const std::string_view& key) override {
        std::shared_ptr<InternalNVSConfigProvider::NVSConfigProviderItem> child = std::make_shared<InternalNVSConfigProvider::NVSConfigProviderItem>(internal, key);
        return Proxy(child);
    }
};
