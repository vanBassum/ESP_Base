#pragma once
#include "esp_system.h"



namespace ESP_Base
{
	class IStream
	{
	public:
		virtual size_t Write(const void* data, size_t size) = 0;	
		virtual size_t Read(void* data, size_t size) = 0;
		
	};
	
	
}


