#pragma once
#include <string>

namespace ESP_Base
{
	
	
	class ISerializable
	{
	public:
		
		virtual std::string ToString() = 0;
		virtual bool TryParse(std::string serial) = 0;
	};
	
	
	
	
}

