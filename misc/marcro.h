#pragma once
#include "esp_log.h"

#define INIT_AND_CONTINUE(TAG_, MESSAGE, FUNC) do {													\
		esp_err_t err_rc_ = FUNC;																	\
		if (err_rc_ == ESP_OK)																		\
			ESP_LOGI(TAG_, "%-64s (%d) %s", MESSAGE, err_rc_, esp_err_to_name(err_rc_));			\
		else																						\
			ESP_LOGE(TAG_, "%-64s (%d) %s", MESSAGE, err_rc_, esp_err_to_name(err_rc_));			\
    } while(0)

#define INIT_OR_RETURN(TAG_, MESSAGE, FUNC) do {													\
		esp_err_t err_rc_ = FUNC;																	\
		if (err_rc_ == ESP_OK)																		\
			ESP_LOGI(TAG_, "%-64s (%d) %s", MESSAGE, err_rc_, esp_err_to_name(err_rc_));			\
		else {																						\
			ESP_LOGE(TAG_, "%-64s (%d) %s", MESSAGE, err_rc_, esp_err_to_name(err_rc_));			\
			return err_rc_;																			\
		}																							\
    } while(0)	    
	    
#define INIT_OR_RETURN_SILENT(FUNC) do {															\
		esp_err_t err_rc_ = FUNC;																	\
		if (err_rc_ != ESP_OK)																		\
			return err_rc_;																			\
    } while(0)

	    