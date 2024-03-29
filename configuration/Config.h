#pragma once
#include <memory>
#include "IConfig.h"
#include "ConfigContainer.h"

class Config
{
    std::shared_ptr<IConfig> container;
    static constexpr inline const char *TAG = "Config";

public:
    Config() : container(std::make_shared<ConfigContainer>("")) {}

    Config(std::shared_ptr<IConfig> cfg) : container(cfg) {}

    Result Add(std::shared_ptr<IConfig> value) { return container->Add(value); }
    Config operator[](const std::string &key) { return (*container)[key]; }

    template <typename T>
    Result Populate(T &value)
    {
        return container->Populate(value);
    }

    template <typename T>
    Result Set(const T &value)
    {
        return container->Set(value);
    }

    template <typename T>
    T GetAs()
    {
        T result;
        Populate(result);
        return result;
    }
};
