#pragma once
#include "setting.h"
#include <string>



class ISettingVisitor
{
public:
	virtual void Visit(Setting<int>* setting) = 0;
	virtual void Visit(Setting<std::string>* setting) = 0;
};
