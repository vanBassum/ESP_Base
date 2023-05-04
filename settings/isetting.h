#pragma once
#include <string>

class ISettingVisitor;

class ISetting
{
public:
	std::string Key;
	
	virtual void Accept(ISettingVisitor* handler) = 0;
	
	ISetting(const std::string key)
	{
		Key = key;
	}
	
};
