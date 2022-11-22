#pragma once
#include "esp_system.h"
#include "stdint.h"
#include "nvs_flash.h"

namespace ESP_Base
{
	
	class INVS
	{
	public:
		
		//virtual esp_err_t NVSStore(nvs_handle_t handle, const char* key) = 0;										
		//virtual esp_err_t NVSLoad(nvs_handle_t handle, const char* key)  = 0;
		//
		//
		//
		//static esp_err_t NVSStore(nvs_handle_t handle, const char* key, INVS* val)  { return val->NVSStore(handle, key);  }											
		//static esp_err_t NVSLoad(nvs_handle_t handle, const char* key, INVS* val)  { return val->NVSLoad(handle, key); 	}

		
		
		static esp_err_t NVSStore(nvs_handle_t handle, const char* key, uint8_t* val)  { return nvs_set_u8(handle, key, *val);  }											
		static esp_err_t NVSLoad(nvs_handle_t handle, const char* key, uint8_t* val)  { return nvs_get_u8(handle, key, val); 	}
		static esp_err_t NVSStore(nvs_handle_t handle, const char* key, uint16_t* val) { return nvs_set_u16(handle, key, *val); }											
		static esp_err_t NVSLoad(nvs_handle_t handle, const char* key, uint16_t* val) { return nvs_get_u16(handle, key, val); 	}
		static esp_err_t NVSStore(nvs_handle_t handle, const char* key, uint32_t* val) { return nvs_set_u32(handle, key, *val); }											
		static esp_err_t NVSLoad(nvs_handle_t handle, const char* key, uint32_t* val) { return nvs_get_u32(handle, key, val); 	}
		static esp_err_t NVSStore(nvs_handle_t handle, const char* key, uint64_t* val) { return nvs_set_u64(handle, key, *val); }											
		static esp_err_t NVSLoad(nvs_handle_t handle, const char* key, uint64_t* val) { return nvs_get_u64(handle, key, val); 	}
		static esp_err_t NVSStore(nvs_handle_t handle, const char* key, int8_t* val)  { return nvs_set_i8(handle, key, *val);   }											
		static esp_err_t NVSLoad(nvs_handle_t handle, const char* key, int8_t* val)  { return nvs_get_i8(handle, key, val); 	}
		static esp_err_t NVSStore(nvs_handle_t handle, const char* key, int16_t* val) { return nvs_set_i16(handle, key, *val);  }											
		static esp_err_t NVSLoad(nvs_handle_t handle, const char* key, int16_t* val) { return nvs_get_i16(handle, key, val); 	}
		static esp_err_t NVSStore(nvs_handle_t handle, const char* key, int32_t* val) { return nvs_set_i32(handle, key, *val);  }											
		static esp_err_t NVSLoad(nvs_handle_t handle, const char* key, int32_t* val) { return nvs_get_i32(handle, key, val); 	}
		static esp_err_t NVSStore(nvs_handle_t handle, const char* key, int64_t* val) { return nvs_set_i64(handle, key, *val);  }											
		static esp_err_t NVSLoad(nvs_handle_t handle, const char* key, int64_t* val) { return nvs_get_i64(handle, key, val); 	}
	};
	
	
	
}

