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

#warning "These macro's are deprecated and should be avoided."



#define DEV_RETURN_ON_FALSE(a, returnValue, log_tag, format, ...) do {                          \
        if (unlikely(!(a))) {                                                                   \
            ESP_LOGE(log_tag, "%s(%d): " format, __FUNCTION__, __LINE__, ##__VA_ARGS__);        \
            return returnValue;                                                                 \
        }                                                                                       \
    } while(0)

#define DEV_RETURN_ON_ERROR(result, log_tag, format, ...) do {                                  \
        if (unlikely((result) != Result::Ok)) {                                           \
            ESP_LOGE(log_tag, "%s(%d): " format, __FUNCTION__, __LINE__, ##__VA_ARGS__);        \
            return result;                                                                      \
        }                                                                                       \
    } while(0)

#define DEV_RETURN_ON_ERROR_SILENT(result) do {                                                 \
        if (unlikely((result) != Result::Ok)) {                                           \
            return result;                                                                      \
        }                                                                                       \
    } while(0)

#define GET_DEV_OR_RETURN(dst, device, newStatus, returnValue, log_tag, format, ...) do {       \
        if (device == NULL) {                                                                   \
            DeviceSetStatus(newStatus);                                                               \
            ESP_LOGE(log_tag, format, ##__VA_ARGS__);                                           \
            return returnValue;                                                                 \
        }                                                                                       \
        dst = device;                                                                           \
    } while (0)



// These are the new macro's

#define RETURN_ON_ERR(result) do {                                                          \
        if (unlikely((result) != Result::Ok)) {                                                 \
            return result;                                                                      \
        }                                                                                       \
    } while(0)

#define RETURN_ON_ERR_LOGE(result, log_tag, format, ...) do {                                           \
        int resultInt = static_cast<int>(result);                                                           \
        if (unlikely(result != Result::Ok)) {                                                               \
            ESP_LOGE(log_tag, "%s:%d, ERR:%d " format, __FUNCTION__, __LINE__, resultInt, ##__VA_ARGS__);   \
            return result;                                                                                  \
        }                                                                                                   \
    } while(0)








#define DEVICE_PROP_STR(val)  {.str = (val)} // Initialize a pointer to a string
#define DEVICE_PROP_I32(val)  {.i32 = (val)} // Initialize an int32_t value
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
