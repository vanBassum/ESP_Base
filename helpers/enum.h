#pragma once

//https://stackoverflow.com/questions/1448396/how-to-use-enums-as-flags-in-c
#define DEFINE_ENUM_FLAG_OPERATORS(T)									 \
	inline T operator~ (T a) { return (T)~(int)a; }                      \
	inline T operator| (T a, T b) { return (T)((int)a | (int)b); }       \
	inline T operator& (T a, T b) { return (T)((int)a & (int)b); }       \
	inline T operator^ (T a, T b) { return (T)((int)a ^ (int)b); }       \
	inline T& operator|= (T& a, T b) { return (T&)((int&)a |= (int)b); } \
	inline T& operator&= (T& a, T b) { return (T&)((int&)a &= (int)b); } \
	inline T& operator^= (T& a, T b) { return (T&)((int&)a ^= (int)b); } 

#define HAS_BIT(a, b) 	( (a & b) == b )
#define HAS_ANY(a) 		( a > 0 )

//https://stackoverflow.com/questions/12059774/c11-standard-conformant-bitmasks-using-enum-class
#define DEFINE_ENUM_CLASS_FLAG_OPERATORS(T, TVAL)								 										\
	inline constexpr T operator&(T x, T y)  { return static_cast<T> (static_cast<TVAL>(x) & static_cast<TVAL>(y));  }  	\
	inline constexpr T  operator|(T x, T y) { return static_cast<T> (static_cast<TVAL>(x) | static_cast<TVAL>(y));  } 	\
	inline constexpr T  operator^(T x, T y) { return static_cast<T> (static_cast<TVAL>(x) ^ static_cast<TVAL>(y));  } 	\
	inline constexpr T  operator~(T x)		{ return static_cast<T> (~static_cast<TVAL>(x));  }                         \
	inline T &  operator&=(T & x, T y)		{ return x = x & y; }                                                      	\
	inline T &  operator|=(T & x, T y)		{ return x = x | y; }                                                      	\
	inline T &  operator^=(T & x, T y)		{ return x = x ^ y; }															





