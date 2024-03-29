#pragma once
#include <memory>
#include "IConfig.h"
#include "ConfigContainer.h"

class Config : public IConfig
{
    std::shared_ptr<IConfig> container;
public:
    Config()  : container(std::make_shared<ConfigContainer>("")) {}

    Config(std::shared_ptr<IConfig> cfg) : container(cfg) {  }

    Result Add(std::shared_ptr<IConfig> value) override { return container->Add(value); }
    Config operator[](const std::string& key) override { return (*container)[key]; }
    Result Populate(std::string& value)  override {return container->Populate(value);}
    Result Set(const std::string& value) override { return container->Set(value); }

    std::string AsString()
    {
        std::string result;
        Populate(result);
        return result;
    }
};
