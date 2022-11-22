#pragma once
#include "icjson.h"
#include "invs.h"
#include "rtos/recursivemutex.h"
#include "esp_log.h"

namespace ESP_Base
{
	class ISetting;
	
	class BaseSettings : public IcJSON
	{
		std::vector<ISetting*> settings;
	protected:
		RecursiveMutex mutex;
				
		void RegisterSetting(ISetting* setting)
		{
			settings.push_back(setting);
		}
		friend ISetting;
		
	public:		
		virtual cJSON* ToJSON() override;
		virtual bool TryParse(cJSON *json) override;
		esp_err_t LoadNVS(const char* nSpace);
		esp_err_t SaveNVS(const char* nSpace);
		
		void PrintAsJSON()
		{
			cJSON* json = ToJSON();
			char*  str = cJSON_Print(json);
			ESP_LOGI("Settings", "Settings = \n%s\n", str);
			free(str);
			cJSON_Delete(json);
		}
	};
	
	
	

	class ISetting : public IcJSON
	{
	protected:
		BaseSettings* base;
		const char* key;
		
		virtual cJSON* ToJSON() = 0;
		virtual bool TryParse(cJSON *json) = 0;
		virtual esp_err_t NVSStore(nvs_handle_t handle) = 0;										
		virtual esp_err_t NVSLoad(nvs_handle_t handle)  = 0;
		void Register()
		{
			base->RegisterSetting(this);
		}
		bool Take(int timeout = portMAX_DELAY)
		{
			return base->mutex.Take(timeout);
		}
		void Give()
		{
			base->mutex.Give();
		}
		friend BaseSettings;
	};
	
	
	template<typename T>
	class Setting : public ISetting
	{
		T Value;
		
	protected:
		cJSON* ToJSON() override
		{
			return IcJSON::ToJSON(&Value);
		}
		bool TryParse(cJSON *json) override
		{
			return IcJSON::TryParse(json, &Value);
		}
		
		virtual esp_err_t NVSStore(nvs_handle_t handle) override
		{
			return INVS::NVSStore(handle, key, &Value);
		}
		virtual esp_err_t NVSLoad(nvs_handle_t handle ) override
		{
			return INVS::NVSLoad(handle, key, &Value);
		}

		
	public:
		Setting(BaseSettings* base, const char* key, T defaultValue)
		{
			this->Value = defaultValue;
			this->base = base;
			this->key = key;
			Register();
		}

		T Get()
		{
			T copy;
			if (Take())
			{
				copy = Value;
				Give();
			}
			return copy;
		}
		
		void Set(T val)
		{
			if (Take())
			{
				Value = val;
				Give();
			}
		}
	};
	

}

