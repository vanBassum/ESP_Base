#pragma once
#include "esp_log.h"
	    
#define INIT_OR_RETURN(_TAG_, _MESSAGE_, FUNC)do {													\
		bool result = (FUNC);																			\
		if (result)																					\
			ESP_LOGI(_TAG_, "%-64s Initialized", _MESSAGE_);										\
		else {																						\
			ESP_LOGE(_TAG_, "%-64s Initialisation Failed", _MESSAGE_);								\
			return false;																			\
		}																							\
    } while(0)	    
	    
	    
#define INIT_AND_CONTINUE(_TAG_, _MESSAGE_, FUNC)do {												\
		bool result = (FUNC);																			\
		if (result)																					\
			ESP_LOGI(_TAG_, "%-64s Initialized", _MESSAGE_);										\
		else {																						\
			ESP_LOGE(_TAG_, "%-64s Initialisation Failed", _MESSAGE_);								\
		}																							\
    } while(0)	     
	    