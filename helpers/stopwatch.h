#pragma once
#include <stdint.h>
#include "esp_timer.h"

class Stopwatch
{
	uint64_t start;
	
	
public:
	
	Stopwatch()
	{
		start = esp_timer_get_time();
	}

	void Restart()
	{
		start = esp_timer_get_time();
	}
	
	uint64_t GetElapsed()
	{
		return esp_timer_get_time() - start;
	}
};