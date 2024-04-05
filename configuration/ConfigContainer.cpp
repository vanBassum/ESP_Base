#include "ConfigContainer.h"
#include "ConfigFactory.h"
#include "Config.h"


ConfigContainer::ConfigContainer(const std::string &key)
{
    _key = key;
}

Result ConfigContainer::Add(std::shared_ptr<IConfig> value)
{
    _value.push_back(value);
    return Result::Ok;
}

Config ConfigContainer::operator[](const std::string &key)
{
    for (auto &config : _value)
    {
        if (config->_key == key)
        {
            return Config(config);
        }
    }
    auto me = shared_from_this();
    _factory = std::make_shared<ConfigFactory>(key, me);
    return Config(_factory);
}

Config ConfigContainer::Iterator::operator*() const
{
    std::shared_ptr<IConfig> cfg = *iter;
    return Config(cfg);
}
