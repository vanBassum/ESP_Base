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

    ConfigTypes GetType() override { return ConfigTypes::Container; }


    // Custom iterator class to iterate over key-value pairs
    class Iterator
    {
    private:
        using IterType = typename std::vector<std::shared_ptr<IConfig>>::iterator;
        IterType iter;

    public:
        explicit Iterator() : iter(IterType()) {}
        explicit Iterator(const IterType& it) : iter(it) {}

        Config operator*() const;

        Iterator& operator++()
        {
            ++iter;
            return *this;
        }

        bool operator!=(const Iterator& other) const
        {
            return iter != other.iter;
        }
    };

    Iterator begin() { return Iterator(_value.begin()); }
    Iterator end() { return Iterator(_value.end()); }
};



