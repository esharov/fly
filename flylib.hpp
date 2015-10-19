#ifndef __FLYLIB_HPP
#define __FLYLIB_HPP

#include "flydef.hpp"
#include <stdlib.h>
#include <string.h>
#include <wchar.h>


typedef void (*entry_t)();

extern entry_t Entry;

void VoidFunc();


inline size_t Length(const char* text) { return strlen(text); }

inline size_t Length(const wchar_t* text) { return wcslen(text); }


template<class buf_a, class val_a>
inline buf_a& Pulse(buf_a& buf, val_a val)
{
	buf = (buf&1)<<1;
	if (val != 0)
	{
		buf |= 1;
	}
	return buf;
}


inline r_t Random()
{
	return r_t(rand())/RAND_MAX;
}

inline int Random(const int inf, const int sup)
{
	const int pow = (RAND_MAX+1)/(sup - inf + 1);
	return inf + rand()/pow;
}



extern wchar_t* Name;

//#define Min(b, a) ( (b) < (a) ? (b) : (a) )

template<class b_a, class a_a>
inline b_a Min(b_a b, a_a a)
{
	return (b < a) ? b : a;
}

template<class b_a, class a_a>
inline b_a Max(b_a b, a_a a)
{
	return (b > a) ? b : a;
}

template<class b_a, class a_a>
inline b_a& High(b_a& b, a_a a)
{
	if (b < a)
	{
		b = a;
	}
	return b;
}


template <class b_a, class a_a>
inline b_a& Low(b_a& b, a_a a)
{
	if (b > a)
	{
		b = a;
	}
	return b;
}

inline r_t Lim(const r_t var, const r_t val_min = 0, const r_t val_max = 1) 
{
	if (var > val_max) return val_max;
	if (var < val_min) return val_min;
	return var;
}

inline r_t LimVar(r_t& var, const r_t val_min = 0, const r_t val_max = 1)
{
	if (var > val_max) var = val_max;
	if (var < val_min) var = val_min;
	return var;
}

template <class var_a, class min_a, class max_a>
inline bool Inc(var_a& var, const min_a min, const max_a max)
{
	var++;
	if (var < min || var > max)
	{
		var = min;
		return 1;
	}
	return 0;
}

template <class var_a, class min_a, class max_a>
inline bool Dec(var_a& var, const min_a min, const max_a max)
{
	var--;
	if (var < min || var > max)
	{
		var = max;
		return 1;
	}
	return 0;
}

struct case_m
{
	size_t* state;
	size_t	test;

	case_m() : state(0), test(0) {}
	case_m(size_t& a_state) : state(&a_state), test(0) {}

	operator size_t&() { return state[0]; }

	operator bool() { return state[0] == test++; }
};
extern case_m Case;

template<size_t size>
struct temp_m
{
	uint8_t		data[size];
	uint8_t*	pointer;

	template<class var_a> temp_m(var_a& var) { memcpy(data, pointer = (uint8_t*)&var, size); }
	~temp_m() { memcpy(pointer, data, size); }
};
#define Keep(var) temp_m<sizeof(var)> temp##var = var; var



#include <iostream>

typedef std::wostringstream text_t;
extern text_t Text;
text_t& Text_New();



const size_t			Stack_Size = 16*1024*1024;
extern uint8_t			Stack_Data[Stack_Size];
extern uint8_t*			Stack_Cur;
extern const uint8_t*	Stack_End;

bool Stack_Set(void* p);


template <class type_a>
inline bool Stack_Push(type_a& o)
{
	if (Stack_End - Stack_Cur >= sizeof(o))
	{
		*(type_a*)Stack_Cur = o;
		Stack_Cur += sizeof(o);
		return 1;
	}
	return 0;
}

template <class type_a>
inline bool Stack_Pop(type_a& o)
{
	if (Stack_Cur - Stack_Data >= sizeof(o))
	{
		Stack_Cur -= sizeof(o);
		o = *(type_a*)Stack_Cur;
		return 1;
	}
	return 0;
}


#endif