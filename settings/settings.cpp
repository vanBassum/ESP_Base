#include "settings.h"
#include "nvs_flash.h"


esp_err_t ESP_Base::BaseSettings::LoadNVS(const char* nspace)
{
	esp_err_t res = ESP_FAIL;
	if (mutex.Take())
	{
		nvs_handle_t handle;
		res = nvs_open(nspace, NVS_READONLY, &handle);
		if (res == ESP_OK)
		{
			int size = settings.size();
			for (int i = 0; i < size; i++)
			{
				res = settings[i]->NVSLoad(handle);
				if (res != ESP_OK)
					break;
			}
		}
		mutex.Give();
	}
	return res;
}

esp_err_t ESP_Base::BaseSettings::SaveNVS(const char* nspace)
{
	esp_err_t res = ESP_FAIL;
	if (mutex.Take())
	{
		nvs_handle_t handle;
		res = nvs_open(nspace, NVS_READWRITE, &handle);
		if (res == ESP_OK)
		{
			int size = settings.size();
			for (int i = 0; i < size; i++)
			{
				res = settings[i]->NVSStore(handle);
				if (res != ESP_OK)
					break;
			}
			if (res == ESP_OK)
				nvs_commit(handle);
			nvs_close(handle);
		}
		mutex.Give();
	}
	return res;
}

cJSON* ESP_Base::BaseSettings::ToJSON()
{
	cJSON* result = NULL;
	if (mutex.Take())
	{
		result = cJSON_CreateObject();
		if (result != NULL)
		{
			int size = settings.size();
			for (int i = 0; i < size; i++)
			{
				cJSON* obj = settings[i]->ToJSON();
				cJSON_AddItemToObject(result, settings[i]->key, obj);
			}
		}
		mutex.Give();
	}
	return result;
}


bool ESP_Base::BaseSettings::TryParse(cJSON *json)
{
	if (json == NULL)
		return false;
	bool success = true;
	if (mutex.Take())
	{
		int size = settings.size();
		for (int i = 0; i < size; i++)
		{
			cJSON* obj = cJSON_GetObjectItem(json, settings[i]->key);
			success &= settings[i]->TryParse(obj);
		}
		mutex.Give();
	}
	else
		success = false;
	return success;
}


