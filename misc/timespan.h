#pragma once

#include <time.h>
#include <string>


namespace ESP_Base
{
	
	class TimeSpan
	{
		time_t ticks = 0;	//Ticks is in miliseconds!
		
	public:
		
		
		TimeSpan()
		{
			ticks = 0;
		}
		
		TimeSpan(time_t miliseconds)
		{
			ticks = miliseconds;
		}

		time_t GetMiliSeconds() const { return ticks; }
		time_t GetSeconds() const { return ticks / 1000; }
		time_t GetMinutes() const { return ticks / 60000; }
		time_t GetHours() const { return ticks / 3600000; }
		time_t GetDays() const { return ticks / 86400000; }

		static TimeSpan FromMiliseconds(const time_t value){ return TimeSpan(value); }
		static TimeSpan FromSeconds(const time_t value){ return TimeSpan(value * 1000); }
		static TimeSpan FromMinutes(const time_t value){ return TimeSpan(value * 60000); }
		static TimeSpan FromHours(const time_t value){ return TimeSpan(value * 3600000);	}
		static TimeSpan FromDays(const time_t value){ return TimeSpan(value * 86400000);	}

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