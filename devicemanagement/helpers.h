#pragma once

#include "esp_system.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <iostream>
#include <cstdint>
#include <functional>
#include <memory>
#include <cstring>
#include "esp_check.h"

#define RETURN_ON_ERR(result) do {                                                          \
        Result res = result;                                                                \
        if (unlikely((res) != Result::Ok)) {                                                 \
            return res;                                                                      \
        }                                                                                       \
    } while(0)

#define RETURN_ON_ERR_LOG(level, result, log_tag, format, ...) do {                                      \
        Result res = result;                                                                            \
        if (unlikely(res != Result::Ok)) {                                                               \
            level(log_tag, "%s:%d, " format, __FUNCTION__, __LINE__, ##__VA_ARGS__);                    \
            return res;                                                                                  \
        }                                                                                                   \
    } while(0)
    
#define RETURN_ON_ERR_LOGE(result, log_tag, format, ...) RETURN_ON_ERR_LOG(ESP_LOGE, result, log_tag, format, ##__VA_ARGS__)
#define RETURN_ON_ERR_LOGW(result, log_tag, format, ...) RETURN_ON_ERR_LOG(ESP_LOGW, result, log_tag, format, ##__VA_ARGS__)
#define RETURN_ON_ERR_LOGI(result, log_tag, format, ...) RETURN_ON_ERR_LOG(ESP_LOGI, result, log_tag, format, ##__VA_ARGS__)
#define RETURN_ON_ERR_LOGD(result, log_tag, format, ...) RETURN_ON_ERR_LOG(ESP_LOGD, result, log_tag, format, ##__VA_ARGS__)
#define RETURN_ON_ERR_LOGV(result, log_tag, format, ...) RETURN_ON_ERR_LOG(ESP_LOGV, result, log_tag, format, ##__VA_ARGS__)


#define DEVICE_PROP_STR(val)  {.str = (val)} // Initialize a pointer to a string
#define DEVICE_PROP_I08(val)  {.i08 = (val)} 
#define DEVICE_PROP_I16(val)  {.i16 = (val)} 
#define DEVICE_PROP_I32(val)  {.i32 = (val)} 
#define DEVICE_PROP_U08(val)  {.u08 = (val)} 
#define DEVICE_PROP_U16(val)  {.u16 = (val)} 
#define DEVICE_PROP_U32(val)  {.u32 = (val)} 

#define DEVICE_END_MARKER  {nullptr, {0}}  // End marker for the device tree



union DevicePropertyValue {
    const char* str;
    int8_t i08;
    int16_t i16;
    int32_t i32;
    uint8_t u08;
    uint16_t u16;
    uint32_t u32;
};

struct DeviceProperty {
    const char* key;
    DevicePropertyValue value;
};

using Device = const DeviceProperty*; 
using DeviceTree = const Device*;   


enum class Result : uint32_t
{
    Ok = 0,                                             /*!< value indicating success (no error) */
    Error = 1,                                          /*!< Generic code indicating failure */
    NotSupported = 2,                                   /*!< Indicates the method or specific configuration isn't supported */
};

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
