#pragma once
#include "isetting.h"
#include <vector>

class ISettingsContainer
{
public:
	std::vector<ISetting*> AllSettings;
};