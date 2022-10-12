#pragma once

#include <time.h>
#include <string>


namespace ESP_Base
{
	
	class TimeSpan
	{
		time_t ticks = 0;
		
	public:
		
		
		TimeSpan()
		{
			ticks = 0;
		}
		
		TimeSpan(int64_t t)
		{
			ticks = t;
		}

		time_t GetSeconds() const { return ticks; }
		time_t GetMinutes() const { return ticks / 60; }
		time_t GetHours() const { return ticks / 3600; }
		time_t GetDays() const { return ticks / 86400; }

		static TimeSpan FromSeconds(const time_t value){ return TimeSpan(value); }
		static TimeSpan FromMinutes(const time_t value){ return TimeSpan(value * 60); }
		static TimeSpan FromHours(const time_t value){ return TimeSpan(value * 3600);	}
		static TimeSpan FromDays(const time_t value){ return TimeSpan(value * 86400);	}

		friend bool operator==(TimeSpan const &lhs, TimeSpan const &rhs) { return lhs.ticks == rhs.ticks; }
		friend bool operator!=(TimeSpan const &lhs, TimeSpan const &rhs) { return lhs.ticks != rhs.ticks; }
		friend bool operator<(TimeSpan const &lhs, TimeSpan const &rhs) { return lhs.ticks < rhs.ticks; }
		friend bool operator>(TimeSpan const &lhs, TimeSpan const &rhs) { return lhs.ticks > rhs.ticks; }
		friend bool operator<=(TimeSpan const &lhs, TimeSpan const &rhs) { return lhs.ticks <= rhs.ticks; }
		friend bool operator>=(TimeSpan const &lhs, TimeSpan const &rhs) { return lhs.ticks >= rhs.ticks; }
		
		friend TimeSpan operator-(TimeSpan const &lhs, TimeSpan const &rhs) { return TimeSpan(lhs.ticks - rhs.ticks); }
		friend TimeSpan operator+(TimeSpan const &lhs, TimeSpan const &rhs) { return TimeSpan(lhs.ticks + rhs.ticks); }
		
		TimeSpan& operator+=(TimeSpan const &rhs) 
		{ 
			this->ticks += rhs.ticks;
			return *this; 
		}
		
		TimeSpan& operator-=(TimeSpan const &rhs) 
		{ 
			this->ticks -= rhs.ticks;
			return *this; 
		}
	};
}