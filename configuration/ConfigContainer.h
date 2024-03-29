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

    void Print(int depth) override {
        std::string indentation(depth * 2, ' '); // Create indentation string with depth * 4 spaces
        printf("%s%s:\n", indentation.c_str(), _key.c_str());

        for (const auto& config : _value) {
            config->Print(depth + 1); // Print each element with increased depth
        }
    }

};
