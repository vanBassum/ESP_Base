#pragma once

#include <string>
#include <ctime>

#include "timespan.h"


namespace ESP_Base
{
	
	class DateTime
	{
		time_t ticks = 0;	//Ticks is in miliseconds!
		
	public:
		DateTime()
		{
			this->ticks = 0;
		}

		DateTime(time_t ticks)
		{
			this->ticks = ticks;
		}
		

		DateTime(std::string datetime, std::string format)
		{
			struct tm result;
			if (strptime(datetime.c_str(), format.c_str(), &result))
			{
				ticks = mktime(&result) * 1000;
			}
		}
		
		static DateTime Now()
		{
			DateTime dt;
			dt.ticks = time(NULL) * 1000;
			return dt;
		}

		static DateTime Parse(const std::string datetime)
		{
			DateTime result;
			struct tm t;
			if (strptime(datetime.c_str(), "%FT%TZ", &t))
			{
				result.ticks = mktime(&t) * 1000;
			}
			return result;
		}
		

		std::string ToString() const
		{
			char buf[sizeof "2011-10-08T07:07:09+0100" + 1];
			time_t t = ticks / 1000;
			strftime(buf, sizeof buf, "%FT%T%z", localtime(&t));
			buf[25] = '\0';
			buf[24] = buf[23];
			buf[23] = buf[22];
			buf[22] = ':';
			return buf;
		}

		
		friend bool operator==(DateTime const &lhs, DateTime const &rhs) { return lhs.ticks == rhs.ticks; }
		friend bool operator!=(DateTime const &lhs, DateTime const &rhs) { return lhs.ticks != rhs.ticks; }
		friend bool operator <(DateTime const &lhs, DateTime const &rhs) { return lhs.ticks  < rhs.ticks; }
		friend bool operator >(DateTime const &lhs, DateTime const &rhs) { return lhs.ticks  > rhs.ticks; }
		friend bool operator<=(DateTime const &lhs, DateTime const &rhs) { return lhs.ticks <= rhs.ticks; }
		friend bool operator>=(DateTime const &lhs, DateTime const &rhs) { return lhs.ticks >= rhs.ticks; }

		friend DateTime operator-(DateTime const &lhs, TimeSpan const &rhs) { return DateTime(lhs.ticks - rhs.GetSeconds()); }
		friend DateTime operator+(DateTime const &lhs, TimeSpan const &rhs) { return DateTime(lhs.ticks + rhs.GetSeconds()); }
		
		DateTime& operator+=(TimeSpan const &rhs) 
		{ 
			this->ticks += rhs.GetSeconds();
			return *this; 
		}
		
		DateTime& operator-=(TimeSpan const &rhs) 
		{ 
			this->ticks -= rhs.GetSeconds();
			return *this; 
		}
	};
	
	
	
}