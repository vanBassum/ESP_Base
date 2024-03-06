#pragma once
#include <string>
#include <any>
#include "helpers.h"
#include "nvs_flash.h"
#include "IConfigProvider.h"


class NVSConfigProvider : public IConfigProvider
{
public:
    class InternalNVSConfigProvider : public std::enable_shared_from_this<InternalNVSConfigProvider> {
        const std::string& partition;
        const std::string& nSpace;
        nvs_handle_t handle = NULL;
    public:

        class NVSConfigProviderItem : public IConfigProvider
        {
            std::shared_ptr<InternalNVSConfigProvider> parent;
            const std::string& key;
        public:
            NVSConfigProviderItem(std::shared_ptr<InternalNVSConfigProvider> parent, const std::string& key) : parent(parent), key(key) {  }
            ~NVSConfigProviderItem(){}

            virtual Result Get(uint8_t* value) override             { return nvs_get_u8(parent->handle, key.c_str(), value) == ESP_OK ? Result::Ok : Result::Error; }
            virtual Result Set(const uint8_t value) override        { return nvs_set_u8(parent->handle, key.c_str(), value) == ESP_OK ? Result::Ok : Result::Error; }



            virtual Result Get(std::string* value) override
            {
                size_t size = 0;
                // Query NVS to determine the length of the string
                esp_err_t err = nvs_get_str(parent->handle, key.c_str(), nullptr, &size);
                if (err != ESP_OK) {
                    ESP_LOGE("NVSConfigProviderItem", "Failed to get string length for key '%s': %s (%d)", key.c_str(), esp_err_to_name(err), err);
                    return Result::Error;
                }
            
                // Allocate buffer based on the determined size
                char* buffer = new char[size];
                err = nvs_get_str(parent->handle, key.c_str(), buffer, &size);
                if (err != ESP_OK) {
                    ESP_LOGE("NVSConfigProviderItem", "Failed to get string for key '%s': %s (%d)", key.c_str(), esp_err_to_name(err), err);
                    delete[] buffer;
                    return Result::Error;
                }
            
                // Assign the string to the output parameter
                *value = std::string(buffer, size);
            
                // Clean up the allocated buffer
                delete[] buffer;
                return Result::Ok;
            }



            virtual Result Set(const std::string value) override { return nvs_set_str(parent->handle, key.c_str(), value.c_str()) == ESP_OK ? Result::Ok : Result::Error; }

        protected:
            Proxy GetProxy(const std::string& key) override {
                assert(false);
            }
        };

        InternalNVSConfigProvider(const std::string& partition, const std::string& nSpace) : partition(partition), nSpace(nSpace)    {  }

        ~InternalNVSConfigProvider()
        {
            if(handle != NULL)
                nvs_close(handle);
        }

        Result Init()
        {
            // Initialize NVS partition
            esp_err_t err = nvs_flash_init_partition(partition.c_str());
            if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
                ESP_ERROR_CHECK(nvs_flash_erase());
                err = nvs_flash_init_partition(partition.c_str());
            }

            if (err != ESP_OK) {
                ESP_LOGE("InternalNVSConfigProvider", "Failed to initialize NVS partition '%s': %s (%d)", partition.c_str(), esp_err_to_name(err), err);
                return Result::Error;
            }

            // Open NVS namespace
            err = nvs_open_from_partition(partition.c_str(), nSpace.c_str(), NVS_READWRITE, &handle);
            if (err != ESP_OK) {
                ESP_LOGE("InternalNVSConfigProvider", "Failed to open NVS '%s'.'%s': %s (%d)", partition.c_str(), nSpace.c_str(), esp_err_to_name(err), err);
                return Result::Error;
            }
            return Result::Ok;
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
    NVSConfigProvider(const std::string& partition, const std::string& nSpace)
    {
        internal = std::make_shared<InternalNVSConfigProvider>(partition, nSpace);
    }

    ~NVSConfigProvider(){}

    Result Init() { return internal->Init(); }

    Result Commit() { return internal->Commit(); }


protected:
    Proxy GetProxy(const std::string& key) override {
        std::shared_ptr<InternalNVSConfigProvider::NVSConfigProviderItem> child = std::make_shared<InternalNVSConfigProvider::NVSConfigProviderItem>(internal, key);
        return Proxy(child);
    }
};
