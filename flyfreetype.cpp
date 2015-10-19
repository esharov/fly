#include "flyfont.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_OUTLINE_H
#include FT_BITMAP_H

FT_Library		Font_Library = 0;
const float		Glyph_Base = 128;

bool Font_Char_Load(FT_Face ft, wchar_t ch, float h) 
{ 
	if (FT_Set_Pixel_Sizes(ft, 0, (FT_UInt)h) == FT_Err_Ok)
	{
		return FT_Load_Char(ft, ch, FT_LOAD_TARGET_NORMAL | FT_LOAD_FORCE_AUTOHINT) == 0;
	}
	return 0;
}

bool Font_Face(char* name)
{
	bool done = 0;	
	if (Font_Library == 0)
	{
		FT_Init_FreeType(&Font_Library);
	}
	if (Font_Library)
	{
		FT_Face ft; 
		if (FT_New_Face(Font_Library, name, 0, &ft) == 0)
		{
			if (FT_Select_Charmap(ft, FT_ENCODING_UNICODE) == 0)
			{
				if ( Font_Char_Load(ft, ' ', Glyph_Base) )
				{
					Face->handle = ft;

					Face->underline 
					= 
						FT_IS_SCALABLE(ft) 
						? -float( FT_MulFix(ft->underline_position, ft->size->metrics.y_scale) )/float(1 << 6)/Glyph_Base
						: 1.f/10.f
					;
					Face->thickness 
					= 
						FT_IS_SCALABLE(ft)
						? float( FT_MulFix(ft->underline_thickness, ft->size->metrics.y_scale) )/float(1 << 6)/Glyph_Base
						: 1.f/14.f
					;
					Face->strikethrough = -(0.5f - Face->underline*2);
					Face->w = float(ft->glyph->metrics.horiAdvance)/float(1 << 6)/Glyph_Base;
					Face->h = float(ft->size->metrics.height)/float(1 << 6)/Glyph_Base;

					done = 1;
				}
			}
			if (!done)
			{
				FT_Done_Face(ft);
			}
		}
	}
	return done;
}

FT_Glyph Glyph_FT = 0;

bool Font_Glyph(wchar_t code, float size, glyph_s* glyph, int* pw, int* ph, int* ppitch, uint8_t** pdata)
{
	FT_Face ft =(FT_Face) Face->handle;
	if ( Font_Char_Load(ft, code, size) )
	{
		if (Glyph_FT)
		{
			FT_Done_Glyph(Glyph_FT);
			Glyph_FT = 0;
		}

		if (FT_Get_Glyph(ft->glyph, &Glyph_FT) == 0)
		{
			FT_Pos weight = 1 << 6;
			FT_Glyph_To_Bitmap(&Glyph_FT, FT_RENDER_MODE_NORMAL, 0, 1);
			FT_Bitmap& bitmap = reinterpret_cast<FT_BitmapGlyph>(Glyph_FT)->bitmap;

			//bitmap.pixel_mode == FT_PIXEL_MODE_MONO

			glyph->l =  float(ft->glyph->metrics.horiBearingX)/float(1<<6)/size;
			glyph->t = -float(ft->glyph->metrics.horiBearingY)/float(1<<6)/size;
			glyph->w =  float(ft->glyph->metrics.width)/float(1<<6)/size;
			glyph->h =  float(ft->glyph->metrics.height)/float(1<<6)/size;

			*pw = bitmap.width;
			*ph = bitmap.rows;
			*ppitch = bitmap.pitch;
			*pdata = bitmap.buffer;
			return 1;
		}
	}
	return 0;
}

float Print_Kerning(const wchar_t ch1, const wchar_t ch2)
{
	FT_Face ft =(FT_Face) Face->handle;
	float w = 0;
	if ( Font_Char_Load(ft, ch1, Glyph_Base) )
	{
		w = float(ft->glyph->metrics.horiAdvance)/float(1<<6)/Glyph_Base;

		if ( FT_HAS_KERNING(ft) )
		{
			FT_Vector kerning;
			FT_Get_Kerning
			(
				ft, 
				FT_Get_Char_Index(ft, ch1), FT_Get_Char_Index(ft, ch2), 
				FT_KERNING_DEFAULT, &kerning
			);
			w += (FT_IS_SCALABLE(ft)) ? float(kerning.x)/float(1 << 6)/Glyph_Base : kerning.x;
		}
	}
	return w;
}