#pragma once
#include "isetting.h"


template<typename T>
class Setting : public ISetting
{
public:
	T Value;
	
	Setting(const std::string key) : ISetting(key)
	{
		
	}
	
	Setting(const std::string key, const T defaultValue) : ISetting(key)
	{
		Value = defaultValue;
	}
	
	void Accept(ISettingVisitor* handler)
	{
		handler->Visit(this);
	}
};
