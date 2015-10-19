#ifndef __FLYFONT_HPP
#define __FLYFONT_HPP

#include <stdint.h>

struct face_s
{
	face_s*			next;
	void*			handle;
	float			w;
	float			h;
	float			thickness;
	float			underline;
	float			strikethrough;
};

struct glyph_s
{
	glyph_s*	next;
	float		l;
	float		t;
	float		w;
	float		h;
	float		u1;
	float		v1;
	float		u2;
	float		v2;
};

extern face_s*			Face;

bool Font_Face(char* name);
bool Font_Glyph(wchar_t code, float size, glyph_s* glyph, int* pw, int* ph, int* ppitch, uint8_t** pdata);
float Print_Kerning(const wchar_t ch1, const wchar_t ch2);

#endif