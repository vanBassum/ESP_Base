#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include "esp_log.h"


template <typename SenderType, typename DataType = void*>  // Add DataType with a default value
class Event {
	typedef std::function<void(SenderType*, const DataType&)> Handler;
	std::vector<Handler> handlers;

	template<typename T, typename... U>
		size_t getAddress(std::function<T(U...)> f) {
			typedef T(fnType)(U...);
			fnType ** fnPointer = f.template target<fnType*>();
			return (size_t) *fnPointer;
		}

	bool Compare(const Handler& a, const Handler& b) {
		// Check if both functions are not empty
		if (a && b) {
			// Use target() to access the stored function objects
			size_t targetA = getAddress(a);
			size_t targetB = getAddress(b);

			// Check if the targets are not null and match
			if (targetA && targetB && targetA == targetB) {
				return true;
			}
		}
		return false;
	}

public:
	void AddHandler(const Handler& handler) {
		handlers.push_back(handler);
	}

	void RemoveHandler(const Handler& handler) {
		auto it = std::remove_if(handlers.begin(),
			handlers.end(),
			[this, &handler](const Handler& storedHandler) {
				return Compare(handler, storedHandler);
			});

		handlers.erase(it, handlers.end());
	}

	void Invoke(SenderType* sender, const DataType& data) {
		for (const auto& handler : handlers) {
			if (handler)
			{
				// Check if the handler is valid before invoking
				handler(sender, data);
			}
		}
	}
};
