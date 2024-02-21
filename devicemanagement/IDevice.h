#pragma once
#include "helpers.h"
#include "deviceConfig.h"


enum class Result : uint32_t
{
    Ok = 0,                                             /*!< value indicating success (no error) */
    Error = 1,                                          /*!< Generic code indicating failure */
    NotSupported = 2,                                   /*!< Indicates the method or specific configuration isn't supported */
};

// DEPRECATED: DeviceResult is deprecated. Use Result instead.
using DeviceResult [[depricated]] = Result;


enum class DeviceStatus : uint32_t
{
    Ready = 0,                                          /*!< Component is initialized and ready to use. */
    Configuring = 1,                                    /*!< Component was created, waiting for configuration. */
    Dependencies = 2,                                   /*!< Component was configured, waiting for dependencies. */
    Initializing = 3,                                   /*!< Component needs initialization. */
    FatalError = 4,                                     /*!< Component is in unrecoverable error state, possibly due to configuration errors. */
    EndOfLife = 5,                                      /*!< Component is at the end of its life, all references should be removed. */
};

constexpr static const char* DeviceStatusStrings[] = {
    "Ready",         
    "Configuring",   
    "Dependencies",  
    "Initializing",  
    "FatalError",    
    "EndOfLife"      
};


class DeviceManager;
class IDevice {
    constexpr static const char* TAG = "IDevice";
    DeviceStatus status = DeviceStatus::Configuring;

public:
    const char* key;

protected: 
    void DeviceSetStatus(DeviceStatus newStatus) 
    {
        // if(newStatus == DeviceStatus::Ready || status == DeviceStatus::Ready)  //Only show transistions from and to Ready
        //     ESP_LOGI(TAG, "'%s' is '%s'", key, DeviceStatusStrings[(int)newStatus]);


        status = newStatus;
    }

public:
    virtual ~IDevice() {}
    virtual Result DeviceSetConfig(IDeviceConfig& config) = 0;
    virtual Result DeviceLoadDependencies(std::shared_ptr<DeviceManager> deviceManager) = 0;
    virtual Result DeviceInit() = 0;
    DeviceStatus DeviceGetStatus() {return status;}
    bool DeviceCheckStatus(DeviceStatus cStatus) { return cStatus == status;}
};
