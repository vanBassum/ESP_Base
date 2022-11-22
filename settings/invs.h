#pragma once
#include "esp_system.h"
#include "stdint.h"
#include "nvs_flash.h"
#include <string>


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

		static esp_err_t NVSStore(nvs_handle_t handle, const char* key, std::string* val)  { return nvs_set_str(handle, key, val->c_str());  }											
		static esp_err_t NVSLoad(nvs_handle_t handle, const char* key, std::string* val)  
		{ 
			size_t size = 0;
			nvs_get_str(handle, key, NULL, &size); 
			char buf[size];
			esp_err_t res = nvs_get_str(handle, key, buf, &size); 
			if (res == ESP_OK)
			{			
				val->erase();
				val->append(buf, size);
			}
			return res;
		}
		
		
		
		
		
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

