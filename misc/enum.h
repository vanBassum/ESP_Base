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

#define HAS_BIT(a, b) 	( (a & b) > 0 )
#define HAS_ANY(a) 		( a > 0 )

