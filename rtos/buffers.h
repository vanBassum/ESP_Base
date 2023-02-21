#pragma once

#include "interfaces/istream.h"
#include "freertos/stream_buffer.h"




namespace ESP_Base
{
	class StreamBuffer : public IStream
	{
		StreamBufferHandle_t handle = NULL;
		
	public:
		
		~StreamBuffer()
		{
			if (handle != NULL)
				vStreamBufferDelete(handle);
		}
		
		bool Init(size_t xBufferSizeBytes, size_t xTriggerLevelBytes)
		{
			handle = xStreamBufferCreate(xBufferSizeBytes, xTriggerLevelBytes);
			return handle != NULL;
		}
		
		
		size_t Read(void* data, size_t size) override
		{
			return xStreamBufferReceive(handle, data, size, portMAX_DELAY);
		}
		
		size_t Write(const void* data, size_t size) override
		{
			return xStreamBufferSend(handle, data, size, portMAX_DELAY);
		}
	};
}



