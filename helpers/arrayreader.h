#pragma once
#include <iostream>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include "esp_log.h"


struct ArrayWriter {
	constexpr const static char* TAG = "ArrayWriter";
	uint8_t* data; // Pointer to the byte array
	size_t index;  // Current index in the array
	size_t size;   // Total size of the array

	// Constructor that initializes the data pointer, index, and size
	ArrayWriter(uint8_t* ptr, size_t bufferSize)
		: data(ptr)
		, index(0)
		, size(bufferSize) {}

	// Append a value to the array and update the index
	template <typename T>
		bool Append(const T& value) {
			if (index + sizeof(value) > size) {
				ESP_LOGE(TAG, "index out of bounds");
				return false;
			}
			
			static_assert(std::is_trivially_copyable<T>::value, "Non-trivially copyable type");
			std::memcpy(&data[index], &value, sizeof(value));
			//ESP_LOG_BUFFER_HEXDUMP(TAG, &data[index], sizeof(value), ESP_LOG_INFO);
			index += sizeof(value);
			return true;
		}
};

struct ArrayReader {
	constexpr const static char* TAG = "ArrayReader";
	const uint8_t* data; // Pointer to the byte array
	size_t index;        // Current index in the array
	size_t size;         // Total size of the array

	// Constructor that initializes the data pointer, index, and size
	ArrayReader(const uint8_t* ptr, size_t bufferSize)
		: data(ptr)
		, index(0)
		, size(bufferSize) {}

	// Get a value from the array at the current index and update the index
	template <typename T>
		bool Read(T& value) {
			if (index + sizeof(value) > size) {
				ESP_LOGE(TAG, "index out of bounds");
				return false;
			}
			static_assert(std::is_trivially_copyable<T>::value, "Non-trivially copyable type");
			std::memcpy(&value, &data[index], sizeof(value));
			index += sizeof(value);
			return true;
		}
};
