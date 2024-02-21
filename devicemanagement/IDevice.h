#pragma once
#include "helpers.h"
#include "deviceConfig.h"





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
