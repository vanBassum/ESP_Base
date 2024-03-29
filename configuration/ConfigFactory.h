#pragma once
#include "IConfig.h"
#include "ConfigString.h"

class ConfigContainer;
class ConfigFactory : public IConfig, public std::enable_shared_from_this<ConfigFactory>
{
    std::shared_ptr<IConfig> _parent = nullptr;
    std::shared_ptr<ConfigFactory> _child = nullptr;

public:
    ConfigFactory(const std::string &key, std::shared_ptr<IConfig> parent);
    Config operator[](const std::string &key) override;
    Result Add(std::shared_ptr<IConfig> value) override;
    virtual Result Populate(std::string &value) override;
    virtual Result Set(const std::string &value) override;
};
