#pragma once
#include <string>
#include "timespan.h"

// Define a default date-time format
#define DEFAULT_DATE_TIME_FORMAT        "%Y-%m-%d %H:%M:%S"

// Enum to specify the DateTime mode (Local or UTC)
enum class DateTimeMode {
    LOCAL,
    UTC
};

/// <summary>
/// The DateTime class represents a point in time and is designed to work with UTC seconds for consistency in time calculations. All internal calculations and storage are based on UTC seconds, ensuring a uniform reference across different time zones. When working with the DateTime class, all arithmetic operations, including addition and subtraction with time spans, are performed using UTC as the baseline.
/// </summary>
class DateTime {
private:
    static constexpr const char* TAG = "DateTime";
    // Member variables
    time_t epochUtcSeconds = 0;

    // Static member functions for time conversion
    static inline time_t convertToLocalTime(const struct tm* timeinfo);
    static inline time_t convertToUtcTime(const struct tm* timeinfo);
    static inline int days_from_epoch(int y, int m, int d);
    static inline time_t timegm(const struct tm* t);
	
	static inline DateTime strptime_fix(const std::string& dateString, const std::string& format, DateTimeMode timeMode);
		
public:
    // Static constants
    static const DateTime InvalidDateTime;

    // Constructors
    DateTime();
    DateTime(time_t epochUtcSeconds);

    time_t GetEpochUtc(DateTimeMode timeMode);

	// Function to get time of day as TimeSpan
	TimeSpan getTimeOfDay(DateTimeMode timeMode = DateTimeMode::LOCAL) const;
	
    // Convert DateTime to string
    std::string toString(const std::string& format = DEFAULT_DATE_TIME_FORMAT, DateTimeMode timeMode = DateTimeMode::LOCAL) const;

    // Convert string to DateTime
    static DateTime FromString(const std::string& dateString, const std::string& format = DEFAULT_DATE_TIME_FORMAT, DateTimeMode timeMode = DateTimeMode::LOCAL);

    // Get the current date and time
    static DateTime Now();


    // Arithmetic operations with TimeSpan
    DateTime operator+(const TimeSpan& duration) const;
    DateTime operator-(const TimeSpan& duration) const;
    DateTime& operator+=(const TimeSpan& duration);
    DateTime& operator-=(const TimeSpan& duration);
    TimeSpan operator-(const DateTime& other) const;

    // Comparison operators
    bool operator==(const DateTime& other) const;
    bool operator!=(const DateTime& other) const;
    bool operator <(const DateTime& other) const;
    bool operator >(const DateTime& other) const;
    bool operator<=(const DateTime& other) const;
    bool operator>=(const DateTime& other) const;
};



