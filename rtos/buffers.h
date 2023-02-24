#pragma once

#include "interfaces/istream.h"
#include "freertos/stream_buffer.h"




namespace ESP_Base
{
	class StreamBuffer : public IStream
	{
		StreamBufferHandle_t handle = NULL;
		
	public:
		
		//Event after bytes have been written to the queue, Use to set task notifications.
		Event<StreamBuffer*> OnWritten;
		
		~StreamBuffer()
		{
			if (handle != NULL)
				vStreamBufferDelete(handle);
		}
		
		bool Init(size_t xBufferSizeBytes, size_t xTriggerLevelBytes)
		{
			if(handle != NULL)
				vStreamBufferDelete(handle);
			handle = xStreamBufferCreate(xBufferSizeBytes, xTriggerLevelBytes);
			return handle != NULL;
		}
		
		size_t GetAvailableBytes()
		{
			if (handle == NULL) return 0;
			return xStreamBufferBytesAvailable(handle);
		}
		
		size_t GetAvailableSpace()
		{
			if (handle == NULL) return 0;
			return xStreamBufferSpacesAvailable(handle);
		}
		
		size_t Read(void* data, size_t size) override
		{
			if (handle == NULL) 
			{
				ESP_LOGE("StreamBuffer", "Buffer not initialized! blocking task");
				vTaskDelay(portMAX_DELAY);
				return 0;
			}
			return xStreamBufferReceive(handle, data, size, portMAX_DELAY);
		}
		
		size_t Write(const void* data, size_t size) override
		{
			if (handle == NULL) 
			{
				ESP_LOGE("StreamBuffer", "Buffer not initialized! blocking task");
				vTaskDelay(portMAX_DELAY);
				return 0;
			}
			size_t result = xStreamBufferSend(handle, data, size, portMAX_DELAY);
			OnWritten.Invoke(this);
			return result;
		}
	};

}



