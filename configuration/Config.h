#pragma once
#include <memory>
#include "IConfig.h"
#include "ConfigContainer.h"

class Config
{
    std::shared_ptr<IConfig> container;
    static constexpr inline const char *TAG = "Config";

public:
    Config() : container(std::make_shared<ConfigContainer>("Root")) {}

    Config(std::shared_ptr<IConfig> cfg) : container(cfg) {}

    Config(Config& cfg) : container(cfg.container) {}

    Result Add(std::shared_ptr<IConfig> value) { return container->Add(value); }
    Config operator[](const std::string &key) { return (*container)[key]; }

    template <typename T>
    Result Populate(T &value)
    {
        return container->Populate(value);
    }

    template <typename T>
    Result Set(const T &value)const
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

    std::string& GetKey() {return container->_key;}

    ConfigTypes GetType() {return container->GetType();}
    virtual void Print(int depth) {container->Print(depth);}



    // Iterator support
    using Iterator = typename ConfigContainer::Iterator;
    Iterator begin() 
    { 
        if (container->GetType() == ConfigTypes::Container)
        {
            std::shared_ptr<ConfigContainer> casted = std::static_pointer_cast<ConfigContainer>(container);
            if (casted)
                return casted->begin();
        }
        return Iterator(); // Return default-constructed iterator if not a container or if cast fails
    }

    Iterator end() 
    { 
        if (container->GetType() == ConfigTypes::Container)
        {
            std::shared_ptr<ConfigContainer> casted = std::static_pointer_cast<ConfigContainer>(container);
            if (casted)
                return casted->end();
        }
        return Iterator(); // Return default-constructed iterator if not a container or if cast fails
    }

};
