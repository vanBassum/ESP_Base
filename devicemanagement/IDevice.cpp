#include "IDevice.h"
#include <sstream>

bool IDevice::isCompatible(const char *checkComp)
{
    // Tokenize the compatibility string and trim whitespaces
    std::vector<std::string> compatibilityList;
    std::istringstream ss(compatibility);
    std::string token;
    while (std::getline(ss >> std::ws, token, ','))
    {
        // Trim leading and trailing whitespaces from the token
        size_t start = token.find_first_not_of(" \t");
        size_t end = token.find_last_not_of(" \t");
        if (start != std::string::npos && end != std::string::npos)
            compatibilityList.push_back(token.substr(start, end - start + 1));
    }

    // Check if the device's compatibility matches any entry in compatibilityList
    for (const auto &comp : compatibilityList)
    {
        if (std::strcmp(checkComp, comp.c_str()) == 0)
        {
            return true; // Found a match
        }
    }

    return false; // No match found
}