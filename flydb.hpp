#ifndef __FLYDB_HPP
#define __FLYDB_HPP

#include <stdint.h>

bool Database(uint8_t** list, uint8_t** unit, size_t unit_size, uint8_t* data, size_t data_size, uint8_t* text, size_t text_size);

template<class uint_a, class data_a, class char_a>
inline bool Database(uint_a** list, uint_a** unit, data_a* data, char_a* text)
{
	return Database((uint8_t**)list, (uint8_t**)unit, sizeof(**unit), (uint8_t*)data, sizeof(*data), (uint8_t*)text, Length(text)*sizeof(*text));  
}

template<class uint_a, class data_a>
inline bool Database(uint_a** list, uint_a** unit, data_a* data)
{
	return Database((uint8_t**)list, (uint8_t**)unit, sizeof(**unit), (uint8_t*)data, sizeof(*data), 0, 0);  
}

template<class uint_a>
inline bool Database(uint_a** list, uint_a** unit, const char* text)
{
	return Database((uint8_t**)list, (uint8_t**)unit, sizeof(**unit), 0, 0, (uint8_t*)text, Length(text)*sizeof(*text)); 
}

template<class uint_a>
inline bool Database(uint_a** list, uint_a** unit, char* text)
{
	return Database((uint8_t**)list, (uint8_t**)unit, sizeof(**unit), 0, 0, (uint8_t*)text, Length(text)*sizeof(*text)); 
}

template<class uint_a>
inline bool Database(uint_a** list, uint_a** unit, const wchar_t* text)
{
	return text ? Database((uint8_t**)list, (uint8_t**)unit, sizeof(**unit), 0, 0, (uint8_t*)text, Length(text)*sizeof(*text)) : 0; 
}

template<class uint_a>
inline bool Database(uint_a** list, uint_a** unit, wchar_t* text)
{
	return Database((uint8_t**)list, (uint8_t**)unit, sizeof(**unit), 0, 0, (uint8_t*)text, Length(text)*sizeof(*text)); 
}

#endif