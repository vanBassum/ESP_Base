#pragma once
#include "esp_log.h"
	    
#define INIT_OR_RETURN(_TAG_, _MESSAGE_, FUNC)do {													\
		bool result = (FUNC);																		\
		if (result)																					\
			ESP_LOGI(_TAG_, "%-*s Initialized",64-strlen(_TAG_), _MESSAGE_);						\
		else {																						\
			ESP_LOGE(_TAG_, "%-*s Initialisation Failed", 64 - strlen(_TAG_), _MESSAGE_);			\
			return false;																			\
		}																							\
    } while(0)	    
	    
	    
#define INIT_AND_CONTINUE(_TAG_, _MESSAGE_, FUNC)do {												\
		bool result = (FUNC);																		\
		if (result)																					\
			ESP_LOGI(_TAG_, "%-*s Initialized",64-strlen(_TAG_), _MESSAGE_);						\
		else {																						\
			ESP_LOGE(_TAG_, "%-*s Initialisation Failed", 64 - strlen(_TAG_), _MESSAGE_);			\
		}																							\
    } while(0)	     
	    