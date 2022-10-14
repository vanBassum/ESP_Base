#pragma once

#include <string>
#include <ctime>

#include "timespan.h"


namespace ESP_Base
{
	
	class DateTime
	{
		time_t seconds = 0;
		
	public:
		DateTime()
		{
			this->seconds = 0;
		}

		DateTime(time_t ticks)
		{
			this->seconds = ticks;
		}
		

		DateTime(std::string datetime, std::string format)
		{
			struct tm result;
			if (strptime(datetime.c_str(), format.c_str(), &result))
			{
				seconds = mktime(&result);
			}
		}
		
		static DateTime Now()
		{
			DateTime dt;
			dt.seconds = time(NULL);
			return dt;
		}

		static DateTime Parse(const std::string datetime)
		{
			DateTime result;
			struct tm t;
			if (strptime(datetime.c_str(), "%FT%TZ", &t))
			{
				result.seconds = mktime(&t);
			}
			return result;
		}
		

		std::string ToString() const
		{
			char buf[sizeof "2011-10-08T07:07:09+0100" + 1];
			time_t t = seconds;
			strftime(buf, sizeof buf, "%FT%T%z", localtime(&t));
			buf[25] = '\0';
			buf[24] = buf[23];
			buf[23] = buf[22];
			buf[22] = ':';
			return buf;
		}

		
		friend bool operator==(DateTime const &lhs, DateTime const &rhs) { return lhs.seconds == rhs.seconds; }
		friend bool operator!=(DateTime const &lhs, DateTime const &rhs) { return lhs.seconds != rhs.seconds; }
		friend bool operator <(DateTime const &lhs, DateTime const &rhs) { return lhs.seconds  < rhs.seconds; }
		friend bool operator >(DateTime const &lhs, DateTime const &rhs) { return lhs.seconds  > rhs.seconds; }
		friend bool operator<=(DateTime const &lhs, DateTime const &rhs) { return lhs.seconds <= rhs.seconds; }
		friend bool operator>=(DateTime const &lhs, DateTime const &rhs) { return lhs.seconds >= rhs.seconds; }

		//friend DateTime operator-(DateTime const &lhs, TimeSpan const &rhs) { return DateTime(lhs.seconds - rhs.GetSeconds()); }
		//friend DateTime operator+(DateTime const &lhs, TimeSpan const &rhs) { return DateTime(lhs.seconds + rhs.GetSeconds()); }
		
		//DateTime& operator+=(TimeSpan const &rhs) 
		//{ 
		//	this->seconds += rhs.GetSeconds();
		//	return *this; 
		//}
		//
		//DateTime& operator-=(TimeSpan const &rhs) 
		//{ 
		//	this->seconds -= rhs.GetSeconds();
		//	return *this; 
		//}
	};
	
	
	
}