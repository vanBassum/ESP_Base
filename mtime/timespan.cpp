#include "timespan.h"



TimeSpan::TimeSpan()	: seconds(0) {}
TimeSpan::TimeSpan(int64_t seconds) : seconds(seconds) {}


int64_t TimeSpan::getSeconds() const {
    return seconds;
}

TimeSpan TimeSpan::operator+(const TimeSpan& other) const {
    return TimeSpan(seconds + other.seconds);
}

TimeSpan TimeSpan::operator-(const TimeSpan& other) const {

    return TimeSpan(seconds - other.seconds);
}


bool TimeSpan::operator==(const TimeSpan& other) const {
    return seconds == other.seconds;
}

bool TimeSpan::operator!=(const TimeSpan& other) const {
    return seconds != other.seconds;
}

bool TimeSpan::operator<(const TimeSpan& other) const {
    return seconds < other.seconds;
}

bool TimeSpan::operator>(const TimeSpan& other) const {
    return seconds > other.seconds;
}

bool TimeSpan::operator<=(const TimeSpan& other) const {
    return seconds <= other.seconds;
}

bool TimeSpan::operator>=(const TimeSpan& other) const {
    return seconds >= other.seconds;
}
