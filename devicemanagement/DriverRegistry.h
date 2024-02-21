#pragma once
#include <functional>
#include <vector>
#include <memory>
#include "IDevice.h"


class DriverRegistry {
    constexpr static const char* TAG = "DriverRegistry";
    struct DriverEntry {
        const char* compatibility;
        std::function<std::shared_ptr<IDevice>()> factory;
    };

    std::vector<DriverEntry> drivers;

public:
    // Register a driver
    template<typename Concrete>
    void RegisterDriver(const char* compatibility) {
        drivers.push_back({compatibility, []() {
            return std::make_shared<Concrete>();
        }});
    }

    // Create a driver based on compatibility field
    Result CreateDriver(std::shared_ptr<DeviceManager> deviceManager, IDeviceConfig& config, std::shared_ptr<IDevice>& result) {
        const char* deviceKey = nullptr;
        const char* compatibility = nullptr;

        RETURN_ON_ERR(config.getProperty("key", &deviceKey));
        RETURN_ON_ERR(config.getProperty("compatible", &compatibility));

        for (const auto& entry : drivers) {
            if (std::strcmp(entry.compatibility, compatibility) == 0) {
                auto device = entry.factory();
                if(device)
                {
                    device->key = deviceKey;
                    device->DeviceSetConfig(config);
                }
                result = device;
                return Result::Ok;
            }
        }

        ESP_LOGE(TAG, "No driver found for compatibility '%s' for device '%s'", compatibility, deviceKey);
        return Result::Error;
    }
};