#include "IConfig.h"
#include "Config.h"

Config IConfig::operator[](const std::string &key)
{
    printf("Not supported\n"); 
    return Config();
}

