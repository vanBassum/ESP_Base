#pragma once


class IStream
{
public:
	virtual size_t Read(uint8_t* buffer, size_t size) = 0;
	virtual size_t Write(const uint8_t* buffer, size_t size) = 0;
	
};



