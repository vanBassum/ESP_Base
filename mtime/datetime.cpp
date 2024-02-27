#include "datetime.h"
#include "esp_log.h"
#include <ctime>
#include <cstdio>
#include <time.h>
#include <string>
#include <iomanip>
#include <sstream>
#include "assert.h"
#include "memory.h"

#define KCTIMEFORMAT	"%d%m%Y%H%M%S"      //Only required for the strptime FIX

//extern "C" char* strptime(const char* s,
//    const char* f,
//    struct tm* tm) {
//    // Isn't the C++ standard lib nice? std::get_time is defined such that its
//    // format parameters are the exact same as strptime. Of course, we have to
//    // create a string stream first, and imbue it with the current C locale, and
//    // we also have to make sure we return the right things if it fails, or
//    // if it succeeds, but this is still far simpler an implementation than any
//    // of the versions in any of the C standard libraries.
//    std::istringstream input(s);
//    input.imbue(std::locale(setlocale(LC_ALL, nullptr)));
//    input >> std::get_time(tm, f);
//    if (input.fail()) {
//        return nullptr;
//    }
//    return (char*)(s + input.tellg());
//}

// Initialize static constants
const DateTime DateTime::InvalidDateTime = DateTime();

// Constructors
DateTime::DateTime() : epochUtcSeconds(0) {}

DateTime::DateTime(time_t epochUtcSeconds) : epochUtcSeconds(epochUtcSeconds) {}

// Convert DateTime to string
std::string DateTime::toString(const std::string& format, DateTimeMode timeMode) const {
    std::tm tm_info = (timeMode == DateTimeMode::LOCAL) ? *std::localtime(&epochUtcSeconds) : *std::gmtime(&epochUtcSeconds);
    size_t size = 80;//strftime(nullptr, 0, format.c_str(), &tm_info) + 1; // Determine the required buffer size +1 for null terminator
    std::string buffer(size, '\0'); // Allocate a buffer of the required size
    strftime(&buffer[0], size, format.c_str(), &tm_info);// Format the time into the buffer
    return buffer;
}

// return DataTime as time_t
time_t DateTime::GetEpochUtc(DateTimeMode timeMode){
    if(timeMode == DateTimeMode::UTC) {
        return epochUtcSeconds;
    }
    else { 
        ESP_LOGE(TAG, "Error time needs to be UTC !");
        assert(false);
    }    
}

bool SetStr_fix(std::string str, int *val)
{
	//Explicitly chosen to not use the KC_functions.
	//We need support for 64bit and singed integers.

	int64_t absVal = 0;
	int len = str.size();
	int i = 0;
	//Skip the minus
	if (str[0] == '-')
		i++;

	for (; i < len; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return false;

		absVal *= 10;
		absVal += str[i] - '0';
	}

	//negate the val if needed.
	*val = absVal * (str[0] == '-' ? -1 : 1);
	return true;
}

// strptime seems broken in current IDF, quick and dirty fix for converting KC timestamps
DateTime DateTime::strptime_fix(const std::string& dateString, const std::string& format, DateTimeMode timeMode)
{
	if (format == KCTIMEFORMAT)
	{
		struct tm val;
		bool suc = true;
		suc &= SetStr_fix(dateString.substr(0, 2), &val.tm_mday);
		suc &= SetStr_fix(dateString.substr(2, 2), &val.tm_mon);
		suc &= SetStr_fix(dateString.substr(4, 4), &val.tm_year);
		suc &= SetStr_fix(dateString.substr(8, 2), &val.tm_hour);
		suc &= SetStr_fix(dateString.substr(10, 2), &val.tm_min);
		suc &= SetStr_fix(dateString.substr(12, 2), &val.tm_sec);

		val.tm_isdst = 1;
		val.tm_mon -= 1;
		val.tm_year -= 1900;
		
		
		time_t time = (timeMode == DateTimeMode::UTC) ? convertToUtcTime(&val) : convertToLocalTime(&val);
		if (time == -1) {
			ESP_LOGE(TAG, "Error converting struct tm to time_t");
			return InvalidDateTime;
		}
		return DateTime(time);
	}
	
	return InvalidDateTime;
}

// Convert string to DateTime
DateTime DateTime::FromString(const std::string& dateString, const std::string& format, DateTimeMode timeMode) {
    struct tm timeinfo = { 0 };
memset(&timeinfo, 0, sizeof (struct tm));
    // Parse the datetime string
    if (strptime(dateString.c_str(), format.c_str(), &timeinfo) == nullptr) {
	    DateTime fix = strptime_fix(dateString, format, timeMode);
	    if (fix != InvalidDateTime)
		    return fix;
	    
	    ESP_LOGE(TAG, "Couldn't parse datetime string, '%s' '%s'", dateString.c_str(), format.c_str());
        return InvalidDateTime;
    }

    time_t time = (timeMode == DateTimeMode::UTC) ? convertToUtcTime(&timeinfo) : convertToLocalTime(&timeinfo);
    if (time == -1) {
        ESP_LOGE(TAG, "Error converting struct tm to time_t");
        return InvalidDateTime;
    }
    return DateTime(time);
}

// Get the current date and time
DateTime DateTime::Now() {
    return DateTime(time(nullptr));
}

// Arithmetic operations with TimeSpan
DateTime DateTime::operator+(const TimeSpan& duration) const {
    return DateTime(epochUtcSeconds + duration.getSeconds());
}

DateTime DateTime::operator-(const TimeSpan& duration) const {
    return DateTime(epochUtcSeconds - duration.getSeconds());
}

// Implement += and -= operators
DateTime& DateTime::operator+=(const TimeSpan& duration) {
    epochUtcSeconds += duration.getSeconds();
    return *this;
}

DateTime& DateTime::operator-=(const TimeSpan& duration) {
    epochUtcSeconds -= duration.getSeconds();
    return *this;
}

TimeSpan DateTime::operator-(const DateTime& other) const {
    return TimeSpan(epochUtcSeconds - other.epochUtcSeconds);
}

// Comparison operators
bool DateTime::operator==(const DateTime& other) const {
    return epochUtcSeconds == other.epochUtcSeconds;
}

bool DateTime::operator!=(const DateTime& other) const {
    return epochUtcSeconds != other.epochUtcSeconds;
}

bool DateTime::operator <(const DateTime& other) const {
    return epochUtcSeconds < other.epochUtcSeconds;
}

bool DateTime::operator >(const DateTime& other) const {
    return epochUtcSeconds > other.epochUtcSeconds;
}

bool DateTime::operator<=(const DateTime& other) const {
    return epochUtcSeconds <= other.epochUtcSeconds;
}

bool DateTime::operator>=(const DateTime& other) const {
    return epochUtcSeconds >= other.epochUtcSeconds;
}

// Static member functions for time conversion
time_t DateTime::convertToLocalTime(const struct tm* timeinfo) {
    struct tm localTimeinfo = *timeinfo;
    localTimeinfo.tm_isdst = -1;  // Manually set tm_isdst to -1 to let mktime determine whether DST is in effect
    return mktime(&localTimeinfo); // Convert struct tm to time_t
}

time_t DateTime::convertToUtcTime(const struct tm* timeinfo) {
    struct tm utcTimeinfo = *timeinfo;
    utcTimeinfo.tm_isdst = 0;  // Manually set tm_isdst to 0 to indicate that UTC is not affected by daylight saving time
    return timegm(&utcTimeinfo); // Convert struct tm to time_t using timegm
}

// Implement getTimeOfDay as TimeSpan
TimeSpan DateTime::getTimeOfDay(DateTimeMode timeMode) const {
	struct tm timeinfo;

	if (timeMode == DateTimeMode::LOCAL)
		timeinfo = *localtime(&epochUtcSeconds);
	else
		timeinfo = *gmtime(&epochUtcSeconds);

	return TimeSpan {
		timeinfo.tm_hour * 3600LL +
		timeinfo.tm_min * 60LL +
		timeinfo.tm_sec
	};
}

// Algorithm: http://howardhinnant.github.io/date_algorithms.html
int DateTime::days_from_epoch(int y, int m, int d)
{
    y -= m <= 2;
    int era = y / 400;
    int yoe = y - era * 400;                                   // [0, 399]
    int doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1;  // [0, 365]
    int doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;           // [0, 146096]
    return era * 146097 + doe - 719468;
}

// It  does not modify broken-down time
time_t DateTime::timegm(const struct tm* t)
{
    if (t == nullptr || t->tm_mon < 0 || t->tm_mon > 11 || t->tm_mday < 1 || t->tm_mday > 31) {
        ESP_LOGE(TAG, "Invalid tm struct in timegm");
        return -1;
    }

    int year = t->tm_year + 1900;
    int month = t->tm_mon;          // 0-11
    if (month > 11)
    {
        year += month / 12;
        month %= 12;
    }
    else if (month < 0)
    {
        int years_diff = (11 - month) / 12;
        year -= years_diff;
        month += 12 * years_diff;
    }
    int days_since_epoch = days_from_epoch(year, month + 1, t->tm_mday);

    return 60 * (60 * (24L * days_since_epoch + t->tm_hour) + t->tm_min) + t->tm_sec;
}

