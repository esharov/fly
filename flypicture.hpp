#ifndef __FLYPICTURE_HPP
#define __FLYPICTURE_HPP

#include "flydef.hpp"

struct texture_s;
extern texture_s* Texture_Load_List;

union rgba_s
{
	struct 
	{
		uint8_t red;
		uint8_t green;
		uint8_t blue;
		uint8_t alpha;
	}
	part;

	uint32_t code;
};

struct picture_c
{
	uint8_t*	data;
	int			w;
	int			h;

	picture_c() : data(0), w(0), h(0) {}

	void reset()
	{
		if (data)
		{
			delete[] data;
			data = 0;
		}
		w = 0;
		h = 0;
	}

	bool load(const char_t* name);

	bool operator() (const char_t* name, texture_s** list = &Texture_Load_List);

	rgba_s* operator[] (int y) { return (rgba_s*)&data[y*w*4]; }
};

#endif