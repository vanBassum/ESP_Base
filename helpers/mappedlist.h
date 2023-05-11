#pragma once
#include <vector>
#include <string>
#include <iterator>

template<typename T>
class MappedList
{
	typedef std::pair<std::string, T> MappedItem;
	std::vector<MappedItem> collections;
public:
	
	bool Add(const std::string& name, T collection)
	{
		collections.push_back({ name, collection });
		return true;
	}

	T GetByKey(const std::string& key)
	{
		for (auto i : collections)
		{
			if (i.first.compare(key) == 0)
				return i.second;
		}
		return NULL;
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
