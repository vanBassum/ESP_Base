#pragma once
#include <functional>
#include <vector>
#include <memory>
#include <sstream>
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

        // Tokenize the compatibility string
        std::vector<std::string> compatibilityList;
        std::stringstream ss(compatibility);
        std::string token;
        while (std::getline(ss >> std::ws, token, ',')) {
            // Trim leading and trailing whitespaces from the token
            size_t start = token.find_first_not_of(" \t");
            size_t end = token.find_last_not_of(" \t");
            if (start != std::string::npos && end != std::string::npos)
                compatibilityList.push_back(token.substr(start, end - start + 1));
        }

        // Iterate through drivers to find a compatible one
        for (const auto& entry : drivers) {
            // Check if any of the compatibility strings match
            for (const auto& comp : compatibilityList) {
                if (std::strcmp(entry.compatibility, comp.c_str()) == 0) {
                    // Create the device using the factory function
                    auto device = entry.factory();
                    if (device) {
                        // Set device configuration
                        device->key = deviceKey;
                        device->compatibility = compatibility;
                        device->DeviceSetConfig(config); // Ensure proper configuration setting

                        // Assign the created device to the result pointer
                        result = device;
                        return Result::Ok;
                    }
                }
            }
        }

        ESP_LOGE(TAG, "No driver found for compatibility '%s' for device '%s'", compatibility, deviceKey);
        return Result::Error;
    }
};
