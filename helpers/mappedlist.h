#pragma once
#include <vector>
#include <string>
#include <iterator>
#include "esp_log.h"

template<typename T>
class MappedList
{
	typedef std::pair<std::string, T> MappedItem;
	std::vector<MappedItem> collections;
public:
	
	T GetByKey(const std::string& key)
	{
		for (auto i : collections)
		{
			if (i.first.compare(key) == 0)
				return i.second;
		}
		return NULL;
	}

	bool Add(const std::string& key, T collection)
	{
		for (auto i : collections)
		{
			if (i.first.compare(key) == 0)
			{
				ESP_LOGE("MappedList", "Key '%s' already exists.", key.c_str());
				return false;
			}
		}
		collections.push_back({ key, collection });
		return true;
	}
	
	std::vector<MappedItem>::iterator begin()
	{
		return collections.begin();
	}
	
	std::vector<MappedItem>::iterator end()
	{
		return collections.end();
	}
};
