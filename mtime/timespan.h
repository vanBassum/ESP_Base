#pragma once

#include <time.h>
#include <string>

	
class TimeSpan
{
	time_t miliseconds = 0;
		
public:
		
		
	TimeSpan()
	{
		miliseconds = 0;
	}
		
	TimeSpan(time_t miliseconds)
	{
		this->miliseconds = miliseconds;
	}
	
	time_t GetTotalMiliSeconds() const { return miliseconds ; }
	time_t GetTotalSeconds() const { return (miliseconds / 1000) ; }
	time_t GetTotalMinutes() const { return (miliseconds / 60000) ; }
	time_t GetTotalHours() const { return (miliseconds /  3600000) ; }
	time_t GetTotalDays() const { return (miliseconds / 86400000) ; }

	time_t GetMiliSeconds() const { return miliseconds % 1000; }
	time_t GetSeconds() const { return (miliseconds / 1000) % 60; }
	time_t GetMinutes() const { return (miliseconds / 60000) % 60; }
	time_t GetHours() const { return (miliseconds /  3600000) % 60; }
	time_t GetDays() const { return (miliseconds / 86400000) % 60; }

	static TimeSpan FromMiliseconds(const time_t value){ return TimeSpan(value); }
	static TimeSpan FromSeconds(const time_t value){ return TimeSpan(value * 1000); }
	static TimeSpan FromMinutes(const time_t value){ return TimeSpan(value * 60000); }
	static TimeSpan FromHours(const time_t value){ return TimeSpan(value * 3600000);	}
	static TimeSpan FromDays(const time_t value){ return TimeSpan(value * 86400000);	}

	friend bool operator==(TimeSpan const &lhs, TimeSpan const &rhs) { return lhs.miliseconds == rhs.miliseconds; }
	friend bool operator!=(TimeSpan const &lhs, TimeSpan const &rhs) { return lhs.miliseconds != rhs.miliseconds; }
	friend bool operator<(TimeSpan const &lhs, TimeSpan const &rhs) { return lhs.miliseconds < rhs.miliseconds; }
	friend bool operator>(TimeSpan const &lhs, TimeSpan const &rhs) { return lhs.miliseconds > rhs.miliseconds; }
	friend bool operator<=(TimeSpan const &lhs, TimeSpan const &rhs) { return lhs.miliseconds <= rhs.miliseconds; }
	friend bool operator>=(TimeSpan const &lhs, TimeSpan const &rhs) { return lhs.miliseconds >= rhs.miliseconds; }
		
	friend TimeSpan operator-(TimeSpan const &lhs, TimeSpan const &rhs) { return TimeSpan(lhs.miliseconds - rhs.miliseconds); }
	friend TimeSpan operator+(TimeSpan const &lhs, TimeSpan const &rhs) { return TimeSpan(lhs.miliseconds + rhs.miliseconds); }
		
	TimeSpan& operator+=(TimeSpan const &rhs) 
	{ 
		this->miliseconds += rhs.miliseconds;
		return *this; 
	}
		
	TimeSpan& operator-=(TimeSpan const &rhs) 
	{ 
		this->miliseconds -= rhs.miliseconds;
		return *this; 
	}
};
