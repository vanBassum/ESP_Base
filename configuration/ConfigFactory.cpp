#include "ConfigFactory.h"
#include "Config.h"
#include "ConfigValue.h"

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
    ESP_LOGE(TAG, "Path not found");
    return Result::Error;
}

Result ConfigFactory::Populate(int8_t &value)
{
    ESP_LOGE(TAG, "Path not found");
    return Result::Error;
}

Result ConfigFactory::Populate(uint8_t &value)
{
    ESP_LOGE(TAG, "Path not found");
    return Result::Error;
}

Result ConfigFactory::Populate(int16_t &value)
{
    ESP_LOGE(TAG, "Path not found");
    return Result::Error;
}

Result ConfigFactory::Populate(uint16_t &value)
{
    ESP_LOGE(TAG, "Path not found");
    return Result::Error;
}

Result ConfigFactory::Populate(int32_t &value)
{
    ESP_LOGE(TAG, "Path not found");
    return Result::Error;
}

Result ConfigFactory::Populate(uint32_t &value)
{
    ESP_LOGE(TAG, "Path not found");
    return Result::Error;
}

Result ConfigFactory::Populate(int64_t &value)
{
    ESP_LOGE(TAG, "Path not found");
    return Result::Error;
}

Result ConfigFactory::Populate(uint64_t &value)
{
    ESP_LOGE(TAG, "Path not found");
    return Result::Error;
}

Result ConfigFactory::Populate(bool &value)
{
    ESP_LOGE(TAG, "Path not found");
    return Result::Error;
}

Result ConfigFactory::Populate(float &value)
{
    ESP_LOGE(TAG, "Path not found");
    return Result::Error;
}

Result ConfigFactory::Populate(double &value)
{
    ESP_LOGE(TAG, "Path not found");
    return Result::Error;
}

Result ConfigFactory::Populate(long double &value)
{
    ESP_LOGE(TAG, "Path not found");
    return Result::Error;
}

Result ConfigFactory::Set(const std::string &value)
{
    std::shared_ptr<ConfigValue<std::string>> conf = std::make_shared<ConfigValue<std::string>>(_key);
    RETURN_ON_ERR(conf->Set(value));
    return _parent->Add(conf);
}

Result ConfigFactory::Set(const char *value)
{
    std::shared_ptr<ConfigValue<std::string>> conf = std::make_shared<ConfigValue<std::string>>(_key);
    RETURN_ON_ERR(conf->Set(value));
    return _parent->Add(conf);
}

Result ConfigFactory::Set(const int8_t &value)
{
    std::shared_ptr<ConfigValue<int8_t>> conf = std::make_shared<ConfigValue<int8_t>>(_key);
    RETURN_ON_ERR(conf->Set(value));
    return _parent->Add(conf);
}

Result ConfigFactory::Set(const uint8_t &value)
{
    std::shared_ptr<ConfigValue<uint8_t>> conf = std::make_shared<ConfigValue<uint8_t>>(_key);
    RETURN_ON_ERR(conf->Set(value));
    return _parent->Add(conf);
}

Result ConfigFactory::Set(const int16_t &value)
{
    std::shared_ptr<ConfigValue<int16_t>> conf = std::make_shared<ConfigValue<int16_t>>(_key);
    RETURN_ON_ERR(conf->Set(value));
    return _parent->Add(conf);
}

Result ConfigFactory::Set(const uint16_t &value)
{
    std::shared_ptr<ConfigValue<uint16_t>> conf = std::make_shared<ConfigValue<uint16_t>>(_key);
    RETURN_ON_ERR(conf->Set(value));
    return _parent->Add(conf);
}

Result ConfigFactory::Set(const int32_t &value)
{
    std::shared_ptr<ConfigValue<int32_t>> conf = std::make_shared<ConfigValue<int32_t>>(_key);
    RETURN_ON_ERR(conf->Set(value));
    return _parent->Add(conf);
}

Result ConfigFactory::Set(const uint32_t &value)
{
    std::shared_ptr<ConfigValue<uint32_t>> conf = std::make_shared<ConfigValue<uint32_t>>(_key);
    RETURN_ON_ERR(conf->Set(value));
    return _parent->Add(conf);
}

Result ConfigFactory::Set(const int64_t &value)
{
    std::shared_ptr<ConfigValue<int64_t>> conf = std::make_shared<ConfigValue<int64_t>>(_key);
    RETURN_ON_ERR(conf->Set(value));
    return _parent->Add(conf);
}

Result ConfigFactory::Set(const uint64_t &value)
{
    std::shared_ptr<ConfigValue<uint64_t>> conf = std::make_shared<ConfigValue<uint64_t>>(_key);
    RETURN_ON_ERR(conf->Set(value));
    return _parent->Add(conf);
}

Result ConfigFactory::Set(const bool &value)
{
    std::shared_ptr<ConfigValue<bool>> conf = std::make_shared<ConfigValue<bool>>(_key);
    RETURN_ON_ERR(conf->Set(value));
    return _parent->Add(conf);
}

Result ConfigFactory::Set(const float &value)
{
    std::shared_ptr<ConfigValue<float>> conf = std::make_shared<ConfigValue<float>>(_key);
    RETURN_ON_ERR(conf->Set(value));
    return _parent->Add(conf);
}

Result ConfigFactory::Set(const double &value)
{
    std::shared_ptr<ConfigValue<double>> conf = std::make_shared<ConfigValue<double>>(_key);
    RETURN_ON_ERR(conf->Set(value));
    return _parent->Add(conf);
}

Result ConfigFactory::Set(const long double &value)
{
    std::shared_ptr<ConfigValue<long double>> conf = std::make_shared<ConfigValue<long double>>(_key);
    RETURN_ON_ERR(conf->Set(value));
    return _parent->Add(conf);
}
