#pragma once
#include "stdint.h"

/// <summary>
/// The TimeSpan class encapsulates a duration of time, measured in seconds. It provides a convenient way to perform arithmetic operations (addition and subtraction) and comparisons between different time spans. This class simplifies time-related calculations, making it easier to work with time intervals in various applications.
/// </summary>
class TimeSpan {
    int64_t seconds;

public:
    // Constructor
	TimeSpan();
    explicit TimeSpan(int64_t seconds);

    // Accessor method
    int64_t getSeconds() const;

    // Arithmetic operators
    TimeSpan operator+(const TimeSpan& other) const;
    TimeSpan operator-(const TimeSpan& other) const;

    // Comparison operators
    bool operator==(const TimeSpan& other) const;
    bool operator!=(const TimeSpan& other) const;
    bool operator<(const TimeSpan& other) const;
    bool operator>(const TimeSpan& other) const;
    bool operator<=(const TimeSpan& other) const;
    bool operator>=(const TimeSpan& other) const;
};


