#include "flydb.hpp"
#include <memory.h>

static uint8_t* Data = 0;

template<class value_a>
inline void Data_Push(value_a& value)
{
	*(value_a*)Data = value;
	Data += sizeof(value);
}

template<class value_a>
inline bool Data_Equ(value_a& value)
{
	bool ret = *(value_a*)Data == value;
	Data += sizeof(value);
	return ret;
}

inline void Data_Push(uint8_t* data, size_t size)
{
	memcpy(Data, data, size);
	Data += size;
}

inline void Data_Zero(size_t size)
{
	memset(Data, 0, size);
	Data += size;
}

inline bool Data_Equ(uint8_t* data, size_t size)
{
	bool ret = memcmp(Data, data, size) == 0;
	Data += size;
	return ret;
}

bool Database(uint8_t** list, uint8_t** unit, size_t unit_size, uint8_t* data, size_t data_size, uint8_t* text, size_t text_size)
{
	if (text_size + data_size > 0xFFFF)
	{
		return 0;
	}
	uint16_t key_size = text_size + data_size;
	for (*unit = *list; *unit; *unit = *(uint8_t**)*unit)
	{
		Data = *unit + unit_size;
		if ( Data_Equ(key_size) )
		{
			if ( Data_Equ(data, data_size) )
			{
				if ( Data_Equ(text, text_size) )
				{
					return 0;
				}
			}
		}
	}

	*unit = new uint8_t[unit_size + sizeof(key_size) + data_size + text_size];
	if (*unit == 0)
	{
		return 0;
	}

	Data = *unit;
	Data_Push(*list);
	Data_Zero(unit_size - sizeof(uint8_t**));
	Data_Push(key_size);
	Data_Push(data, data_size);
	Data_Push(text, text_size);
	*list = *unit;
	return 1;
}