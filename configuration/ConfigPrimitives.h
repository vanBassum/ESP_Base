#pragma once
#include "IConfig.h"

#define POPULATE(TYPE, VAL) do {                    \
        if(_valueType == TYPE) {                    \
            value = VAL;                            \
            return Result::Ok;                      \
        } else {                                    \
            ESP_LOGE(TAG, "Wrong type");            \
            return Result::Error;                   \
        }                                           \
    } while(0)

enum class PrimitiveTypeEnum {
    EMPTY,
    INT8,
    UINT8,
    INT16,
    UINT16,
    INT32,
    UINT32,
    INT64,
    UINT64,
    BOOL,
    FLOAT,
    DOUBLE,
    LONG_DOUBLE
};

union PrimitiveTypes {
    int8_t i8;
    uint8_t u8;
    int16_t i16;
    uint16_t u16;    
    int32_t i32;
    uint32_t u32;    
    int64_t i64;
    uint64_t u64;   
    bool vBool;
    float vFloat;
    double vDouble;
    long double blongDouble;
};


class ConfigPrimitives : public IConfig
{
    static constexpr inline const char* TAG = "ConfigPrimitives";
    PrimitiveTypeEnum _valueType = PrimitiveTypeEnum::EMPTY;
    PrimitiveTypes _value;
public:
    ConfigPrimitives(const std::string& key)
    {
        _key = key;
    }

Result Populate(int8_t& value) override {
        POPULATE(PrimitiveTypeEnum::INT8, _value.i8);
    }
    Result Populate(uint8_t& value) override {
        POPULATE(PrimitiveTypeEnum::UINT8, _value.u8);
    }
    Result Populate(int16_t& value) override {
        POPULATE(PrimitiveTypeEnum::INT16, _value.i16);
    }
    Result Populate(uint16_t& value) override {
        POPULATE(PrimitiveTypeEnum::UINT16, _value.u16);
    }
    Result Populate(int32_t& value) override {
        POPULATE(PrimitiveTypeEnum::INT32, _value.i32);
    }
    Result Populate(uint32_t& value) override {
        POPULATE(PrimitiveTypeEnum::UINT32, _value.u32);
    }
    Result Populate(int64_t& value) override {
        POPULATE(PrimitiveTypeEnum::INT64, _value.i64);
    }
    Result Populate(uint64_t& value) override {
        POPULATE(PrimitiveTypeEnum::UINT64, _value.u64);
    }
    Result Populate(bool& value) override {
        POPULATE(PrimitiveTypeEnum::BOOL, _value.vBool);
    }
    Result Populate(float& value) override {
        POPULATE(PrimitiveTypeEnum::FLOAT, _value.vFloat);
    }
    Result Populate(double& value) override {
        POPULATE(PrimitiveTypeEnum::DOUBLE, _value.vDouble);
    }
    Result Populate(long double& value) override {
        POPULATE(PrimitiveTypeEnum::LONG_DOUBLE, _value.blongDouble);
    }

    Result Set(const int8_t& value) override {
        _valueType = PrimitiveTypeEnum::INT8;
        _value.i8 = value;
        return Result::Ok;
    }
    Result Set(const uint8_t& value) override {
        _valueType = PrimitiveTypeEnum::UINT8;
        _value.u8 = value;
        return Result::Ok;
    }
    Result Set(const int16_t& value) override {
        _valueType = PrimitiveTypeEnum::INT16;
        _value.i16 = value;
        return Result::Ok;
    }
    Result Set(const uint16_t& value) override {
        _valueType = PrimitiveTypeEnum::UINT16;
        _value.u16 = value;
        return Result::Ok;
    }
    Result Set(const int32_t& value) override {
        _valueType = PrimitiveTypeEnum::INT32;
        _value.i32 = value;
        return Result::Ok;
    }
    Result Set(const uint32_t& value) override {
        _valueType = PrimitiveTypeEnum::UINT32;
        _value.u32 = value;
        return Result::Ok;
    }
    Result Set(const int64_t& value) override {
        _valueType = PrimitiveTypeEnum::INT64;
        _value.i64 = value;
        return Result::Ok;
    }
    Result Set(const uint64_t& value) override {
        _valueType = PrimitiveTypeEnum::UINT64;
        _value.u64 = value;
        return Result::Ok;
    }
    Result Set(const bool& value) override {
        _valueType = PrimitiveTypeEnum::BOOL;
        _value.vBool = value;
        return Result::Ok;
    }
    Result Set(const float& value) override {
        _valueType = PrimitiveTypeEnum::FLOAT;
        _value.vFloat = value;
        return Result::Ok;
    }
    Result Set(const double& value) override {
        _valueType = PrimitiveTypeEnum::DOUBLE;
        _value.vDouble = value;
        return Result::Ok;
    }
    Result Set(const long double& value) override {
        _valueType = PrimitiveTypeEnum::LONG_DOUBLE;
        _value.blongDouble = value;
        return Result::Ok;
    }
};



