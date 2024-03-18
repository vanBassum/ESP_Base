#pragma once
#include "helpers.h"
#include "deviceConfig.h"

class DeviceManager;
class IDevice
{
    constexpr static const char *TAG = "IDevice";
    DeviceStatus status = DeviceStatus::Configuring;

public:
    const char *key;
    const char *compatibility;

protected:
    void DeviceSetStatus(DeviceStatus newStatus) { status = newStatus; ESP_LOGI(TAG,"DeviceSetStatus  %s = %s", key, DeviceStatusStrings[(int)newStatus]); }

public:
    virtual ~IDevice() {}
    virtual Result DeviceSetConfig(IDeviceConfig &config) = 0;
    virtual Result DeviceLoadDependencies(std::shared_ptr<DeviceManager> deviceManager) = 0;
    virtual Result DeviceInit() = 0;
    DeviceStatus DeviceGetStatus() { return status; }
    Result DeviceCheckStatus(DeviceStatus cStatus) { return cStatus == status ? Result::Ok : Result::Error; }
    bool isCompatible(const char *compatibility);
};
