#pragma once
#include "IConfig.h"

class ConfigFactory;
class ConfigContainer : public IConfig, public std::enable_shared_from_this<ConfigContainer>
{
    std::vector<std::shared_ptr<IConfig>> _value;
    std::shared_ptr<ConfigFactory> _factory = nullptr;

public:
    ConfigContainer(const std::string& key);
    Result Add(std::shared_ptr<IConfig> value) override;
    Config operator[](const std::string& key) override;
};
