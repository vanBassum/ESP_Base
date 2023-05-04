#pragma once
#include "setting.h"
#include <string>



class ISettingVisitor
{
public:
	virtual void Visit(Setting<uint32_t>* setting) = 0;
	virtual void Visit(Setting<std::string>* setting) = 0;
};
