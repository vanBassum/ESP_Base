#include "ConfigFactory.h"
#include "Config.h"

ConfigFactory::ConfigFactory(const std::string &key, std::shared_ptr<IConfig> parent)
{
    _key = key;
    _parent = parent;
}

Config ConfigFactory::operator[](const std::string &key)
{
    _child = std::make_shared<ConfigFactory>(key, shared_from_this());
    return Config(_child);
    ;
}

Result ConfigFactory::Add(std::shared_ptr<IConfig> value)
{
    std::shared_ptr<ConfigContainer> container = std::make_shared<ConfigContainer>(_key);
    RETURN_ON_ERR(container->Add(value));
    return _parent->Add(container);
}

Result ConfigFactory::Populate(std::string &value)
{
    printf("Path not found \n");
    return Result::Error;
}

Result ConfigFactory::Set(const std::string &value)
{
    std::shared_ptr<ConfigString> conf = std::make_shared<ConfigString>(_key);
    RETURN_ON_ERR(conf->Set(value));
    return _parent->Add(conf);
}
