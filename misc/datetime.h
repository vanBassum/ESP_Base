#pragma once

#include <string>
#include <ctime>

#include "timespan.h"
#include "string.h"

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

		void Set(time_t ticks)
		{
			seconds = ticks;
		}
		

		void Set(std::string datetime, std::string format = "%FT%TZ")
		{
			struct tm result;
			if (strptime(datetime.c_str(), format.c_str(), &result))
			{
				seconds = mktime(&result);
			}
		}
		
		void Set(struct tm * timeptr)
		{
			seconds = mktime(timeptr);
		}
		
		
		void Get(struct tm * timeptr)
		{
			struct tm *val = localtime(&seconds);
			memcpy(timeptr, val, sizeof(struct tm));
		}
		
		
		
		static DateTime Now()
		{
			DateTime dt;
			dt.seconds = time(NULL);
			return dt;
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