#pragma once
#include "IConfig.h"
#include "ConfigString.h"

class ConfigContainer;
class ConfigFactory : public IConfig, public std::enable_shared_from_this<ConfigFactory>
{
    static constexpr inline const char* TAG = "ConfigFactory";
    std::shared_ptr<IConfig> _parent = nullptr;
    std::shared_ptr<ConfigFactory> _child = nullptr;

public:
    ConfigFactory(const std::string &key, std::shared_ptr<IConfig> parent);
    Config operator[](const std::string &key) override;
    Result Add(std::shared_ptr<IConfig> value) override;


    virtual Result Populate(std::string &value) override;
    virtual Result Populate(int8_t &value) override ;
    virtual Result Populate(uint8_t &value) override ;
    virtual Result Populate(int16_t &value) override ;
    virtual Result Populate(uint16_t &value) override ;
    virtual Result Populate(int32_t &value) override ;
    virtual Result Populate(uint32_t &value) override ;
    virtual Result Populate(int64_t &value) override ;
    virtual Result Populate(uint64_t &value) override ;
    virtual Result Populate(bool &value) override ;
    virtual Result Populate(float &value) override ;
    virtual Result Populate(double &value) override ;
    virtual Result Populate(long double &value) override ;

    virtual Result Set(const std::string &value) override;
    virtual Result Set(const char* value) override;
    virtual Result Set(const int8_t &value) override ;
    virtual Result Set(const uint8_t &value) override ;
    virtual Result Set(const int16_t &value) override ;
    virtual Result Set(const uint16_t &value) override ;
    virtual Result Set(const int32_t &value) override ;
    virtual Result Set(const uint32_t &value) override ;
    virtual Result Set(const int64_t &value) override ;
    virtual Result Set(const uint64_t &value) override ;
    virtual Result Set(const bool &value) override ;
    virtual Result Set(const float &value) override ;
    virtual Result Set(const double &value) override ;
    virtual Result Set(const long double &value) override ;


};

