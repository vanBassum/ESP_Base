#pragma once
#include "cJSON.h"
#include "stdint.h"
#include <string>
#include <vector>
#include "iserializable.h"

#define MTOJSON(type, assignement)			static cJSON* ToJSON(type* val)						\
											{													\
												return assignement;								\
											}														


#define MTRYPARSE(type, cond, assignement)	static bool TryParse(cJSON* json, type* val)		\
											{													\
												if(cond)										\
												{												\
													assignement;								\
													return true;								\
												}												\
												return false;									\
											}




namespace ESP_Base
{
	
	
	class IcJSON
	{
	public:
	
		virtual cJSON* ToJSON() = 0;
		virtual bool TryParse(cJSON *json) = 0;
		
		MTOJSON(IcJSON, val->ToJSON())
		MTRYPARSE(IcJSON, true, val->TryParse(json))
		MTOJSON(std::string, cJSON_CreateString(val->c_str()))
		MTRYPARSE(std::string, cJSON_IsString(json), *val = std::string(json->valuestring))
		MTOJSON(ISerializable, cJSON_CreateString(val->ToString().c_str()))
		MTRYPARSE(ISerializable, cJSON_IsString(json), val->TryParse(std::string(json->valuestring)))
		MTOJSON(bool, cJSON_CreateBool(*val))
		MTRYPARSE(bool, cJSON_IsBool(json), *val = cJSON_IsTrue(json))	
		MTOJSON(float, cJSON_CreateNumber(*val))
		MTRYPARSE(float, cJSON_IsNumber(json), *val = json->valuedouble)
		MTOJSON(double, cJSON_CreateNumber(*val))
		MTRYPARSE(double, cJSON_IsNumber(json), *val = json->valuedouble)
		MTOJSON(int8_t, cJSON_CreateNumber(*val))
		MTRYPARSE(int8_t, cJSON_IsNumber(json), *val = json->valueint)
		MTOJSON(int16_t, cJSON_CreateNumber(*val))
		MTRYPARSE(int16_t, cJSON_IsNumber(json), *val = json->valueint)
		MTOJSON(int32_t, cJSON_CreateNumber(*val))
		MTRYPARSE(int32_t, cJSON_IsNumber(json), *val = json->valueint)
		MTOJSON(uint8_t, cJSON_CreateNumber(*val))
		MTRYPARSE(uint8_t, cJSON_IsNumber(json), *val = json->valueint)
		MTOJSON(uint16_t, cJSON_CreateNumber(*val))
		MTRYPARSE(uint16_t, cJSON_IsNumber(json), *val = json->valueint)
		MTOJSON(uint32_t, cJSON_CreateNumber(*val))
		MTRYPARSE(uint32_t, cJSON_IsNumber(json), *val = json->valueint)
			
			
			
			
			
		//template<typename T>
		//static cJSON* ToJSON(std::vector<T>* val)
		//{
		//	cJSON* json = cJSON_CreateArray();
		//	for (int i = 0; i < val->size(); i++)
		//	{
		//		cJSON_AddItemToArray(json, IcJSON::ToJSON((*val)[i]));
		//	}
		//
		//	return json;
		//}
		//
		//template<typename T>
		//static bool TryParse(cJSON* json, std::vector<T>* val)
		//{
		//	cJSON* iterator;
		//	cJSON_ArrayForEach(iterator, json) 
		//	{
		//		T* obj = new T;
		//		IcJSON::TryParse(iterator, *obj);	
		//		val->push_back(*obj);
		//	}
		//	return true;
		//}
			
			
			
	};
	
	
	
	
}

