#pragma once
#include "rtos/task.h"
#include "helpers.h"
#include "DriverRegistry.h"
#include "IDeviceDetector.h"
#include "IDevice.h"
#include <vector>

class DeviceManager : public std::enable_shared_from_this<DeviceManager> {
    constexpr static const char* TAG = "DeviceManager";
public:
    struct Config {
        TickType_t scanInterval = pdMS_TO_TICKS(1000);
    };
private:
    Task task;
    Config config_;
    bool initialized_ = false;
    std::shared_ptr<DriverRegistry> driverRegistry;
    std::vector<std::shared_ptr<IDeviceDetector>> detectors;
    std::vector<std::shared_ptr<IDevice>> devices;
    std::vector<std::function<void(std::shared_ptr<IDevice> device)>> devicesChangedCallbacks;

    void NotifyChanges(std::shared_ptr<IDevice> device)
    {
         for (const auto& callback : devicesChangedCallbacks) {
            callback(device);
        }
    }

    // Create a new device based on the configuration
    Result CreateDevice(IDeviceConfig& config) {
        const char* deviceKey = nullptr;
        RETURN_ON_ERR(config.getProperty("key", &deviceKey));

        // Check if a device with this key already exists
        if (std::any_of(devices.begin(), devices.end(), [deviceKey](const auto& device) {
            return std::strcmp(device->key, deviceKey) == 0;
        })) {
            //ESP_LOGW(TAG, "Device with key %s already exists", deviceKey);
            return Result::Error;
        }

        // Create a new device
        //ESP_LOGI(TAG, "Creating device '%s'", deviceKey);
        std::shared_ptr<IDevice> device;
        RETURN_ON_ERR(driverRegistry->CreateDriver(shared_from_this(), config, device));
        if(device)
        {
            devices.push_back(device);
            return Result::Ok;
        }
        return Result::Error;
    }

    enum PollResult : uint8_t
    {
        NONE        = 0x00,
        CHANGED     = 0x01,
        ENDOFLIFE   = 0x02,
        HALT        = 0x04,
        NOTIFY      = 0x08,
    };

    PollResult pollDevice(std::shared_ptr<IDevice> device)
    {
        switch (device->DeviceGetStatus())
        {
        case DeviceStatus::Dependencies: 
            return device->DeviceLoadDependencies(shared_from_this()) == Result::Ok ? PollResult::CHANGED : PollResult::NONE;

        case DeviceStatus::Initializing:
            return (PollResult)((device->DeviceInit() == Result::Ok) ? (PollResult::CHANGED | PollResult::NOTIFY) : PollResult::NONE);

        case DeviceStatus::EndOfLife:
            return (PollResult)(PollResult::CHANGED | PollResult::ENDOFLIFE | PollResult::NOTIFY);

        case DeviceStatus::FatalError:
            ESP_LOGE(TAG, "Device '%s' in fatal error state.", device->key);
            return (PollResult)(PollResult::CHANGED | PollResult::HALT | PollResult::NOTIFY);

        case DeviceStatus::Configuring:                 // Something was wrong in the device configuration
            ESP_LOGE(TAG, "Configuration for device '%s' is invalid.", device->key);
            return (PollResult)(PollResult::CHANGED | PollResult::HALT | PollResult::NOTIFY);

        case DeviceStatus::Ready:
            return PollResult::NONE;
        }

        return PollResult::NONE;
    }

    void work() {
        while (true) {
            bool reScan = false;

            for (auto it = devices.begin(); it != devices.end();) {
                std::shared_ptr<IDevice> device = *it;

                PollResult stat = pollDevice(device);

                if(stat & PollResult::CHANGED)
                {
                    DeviceStatus deviceStatus = device->DeviceGetStatus();
                    if(deviceStatus == DeviceStatus::Ready)
                        ESP_LOGI(TAG, "Device '%s' is '%s'", device->key, DeviceStatusStrings[(int)deviceStatus]);

                    if(deviceStatus == DeviceStatus::EndOfLife)
                        ESP_LOGW(TAG, "Device '%s' is '%s'", device->key, DeviceStatusStrings[(int)deviceStatus]);

                    if(deviceStatus == DeviceStatus::FatalError)
                        ESP_LOGE(TAG, "Device '%s' is '%s'", device->key, DeviceStatusStrings[(int)deviceStatus]);

                    reScan = true;
                }

                if(stat & PollResult::NOTIFY)
                {
                    NotifyChanges(device);
                }

                if(stat & PollResult::HALT)
                {
                    assert(false && "Device is in unrecoverable state.");  
                }
                    
                if(stat & PollResult::ENDOFLIFE)
                {
                    it = devices.erase(it);
                }
                else
                {
                    ++it; // Move to the next device
                }
            }

            // Loop through detectors to find new devices
            for (auto& detector : detectors) {
                detector->search([&](IDeviceConfig& config) {
                    reScan |= CreateDevice(config)==Result::Ok;
                });
            }

            if(!reScan)
                vTaskDelay(config_.scanInterval);
        }
    }



public:
    DeviceManager(std::shared_ptr<DriverRegistry> driverRegistry) : driverRegistry(driverRegistry) {};

    void setConfig(const Config& newConfig) {
        assert(!initialized_ && "Config cannot be changed after initialization");
        config_ = newConfig;
    }

    void init() {
        assert(!initialized_ && "Already initialized");
        initialized_ = true;
        task.Init(TAG, 7, 1024 * 4);
        task.SetHandler([&](){work();});
        task.Run();
    }
    
    bool isInitialized() const {
        return initialized_;
    }

    // Register a new detector

    Result RegisterDetector(std::shared_ptr<IDeviceDetector> detector) {
        assert(initialized_);
        detectors.push_back(detector);
        return Result::Ok;
    }

    template<typename Device>
    Result getDeviceByKey(const char* key, std::shared_ptr<Device>& dev) {
        assert(initialized_);
        auto it = std::find_if(devices.begin(), devices.end(), [key](const auto& device) {
            return std::strcmp(device->key, key) == 0;
        });

        if (it != devices.end()) {
            std::shared_ptr<IDevice> genDevice = std::static_pointer_cast<IDevice>(*it);
            RETURN_ON_ERR(genDevice->DeviceCheckStatus(DeviceStatus::Ready));
            // Attempt to cast to the specified Device type TODO: Add typeinformation to IDevice to prevent problems!
            std::shared_ptr<Device> castedDevice = std::static_pointer_cast<Device>(genDevice);
            dev = castedDevice;
            return Result::Ok;
        }
        //ESP_LOGW(TAG, "Device with key '%s' not found", key);
        return Result::Error;
    }

    template<typename Device>
    Result getDeviceByCompatibility(const char* compatibility, std::shared_ptr<Device>& dev) {
        assert(initialized_); // Ensure the collection of devices is initialized

        // Find the device with the specified compatibility
        auto it = std::find_if(devices.begin(), devices.end(), [compatibility](const auto& device) {
            return device->isCompatible(compatibility); // Check compatibility
        });

        if (it != devices.end()) {
            std::shared_ptr<IDevice> genDevice = std::static_pointer_cast<IDevice>(*it);
            RETURN_ON_ERR(genDevice->DeviceCheckStatus(DeviceStatus::Ready));
            // Attempt to cast to the specified Device type TODO: Add typeinformation to IDevice to prevent problems!
            std::shared_ptr<Device> castedDevice = std::static_pointer_cast<Device>(genDevice);
            dev = castedDevice;
            return Result::Ok;
        }

        // Log a warning if no device with the specified compatibility is found
        // ESP_LOGW(TAG, "Device with compatibility '%s' not found", compatibility);

        // Return an error result
        return Result::Error;
    }


    void registerDeviceChangedCallback(const std::function<void(std::shared_ptr<IDevice>)>& callback) {
        devicesChangedCallbacks.push_back(callback);
    }
};
