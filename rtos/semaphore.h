#pragma once


#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"


class Semaphore
{
	SemaphoreHandle_t handle = NULL;
public:
	Semaphore()
	{
		handle = xSemaphoreCreateBinary();
	}
		
	~Semaphore()
	{
		if (handle != NULL)
			vSemaphoreDelete(handle);
	}
		
	bool Take(TickType_t timeout = portMAX_DELAY)
	{
		return xSemaphoreTake(handle, timeout) == pdTRUE;
	}

	bool Give()
	{
		return xSemaphoreGive(handle) == pdTRUE;
	}

};