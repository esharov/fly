#include "flyopengl.hpp"
#include "flydb.hpp"
#include "flyfont.hpp"

struct glyph_kit_s
{
	glyph_kit_s*	next;
	glyph_s*		list;
	int				x;
	int				y;
};

char*			Font = "segoeui.ttf";
r_t				Font_H = 0.1;
bool			Underlined = 0;
bool			Strikethrough = 0;


face_s*			Face_List = 0;
face_s*			Face = 0;

GLuint			Print_Texture = 0;
int				Print_Texture_Y = 0;
const size_t	Print_Texture_W = 1024;
const size_t	Print_Texture_H = 4096;

uint16_t		Glyph_Grid = 128;
glyph_kit_s*	Glyph_List = 0;
glyph_kit_s*	Glyph_Kit = 0;
glyph_s*		Glyph = 0;
uint16_t		Glyph_H;




bool Print_Glyph(const wchar_t code)
{
	Glyph = 0;
	Glyph_Kit = 0;
	if (Print_Texture == 0)
	{
		if ( Texture_Open(&Print_Texture, Print_Texture_W, Print_Texture_H) )
		{
			uint32_t image[4] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, Print_Texture);
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 2, 2, GL_RGBA, GL_UNSIGNED_BYTE, image);
			glFlush();
			Print_Texture_Y = 4;
		}
	}
	if (Print_Texture == 0)
	{
		return 0;
	}
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Print_Texture);

	if ( Database(&Glyph_List, &Glyph_Kit, &Glyph_H) )
	{
		if (Print_Texture_Y + Glyph_H < Print_Texture_H)
		{
			Glyph_Kit->x = 0;
			Glyph_Kit->y = Print_Texture_Y;
			Print_Texture_Y += Glyph_H + 2;
		}
		else
		{
			// удалить из списка
			Glyph_Kit = 0;
		}
	}
	if (Glyph_Kit)
	{
		struct glyph_key_s
		{
			face_s*	font;
			wchar_t	code;
		}
		key = { Face, code };
		if ( Database(&Glyph_Kit->list, &Glyph, &key) ) 
		{
			bool ready = 0;  
			int width;
			int height;
			int pitch;
			uint8_t* data;
			if ( Font_Glyph(code,  Glyph_H, Glyph, &width, &height, &pitch, &data) )
			{
				ready = 1;
				if (Glyph_Kit->x + width >= Print_Texture_W)
				{
					if (width <= Print_Texture_W && Print_Texture_Y + Glyph_H + 2 <= Print_Texture_H)
					{
						Glyph_Kit->y = Print_Texture_Y;
						Glyph_Kit->x = 0;
						Print_Texture_Y += Glyph_H + 2;
					}
					else
					{
						ready = 0;
					}
				}
				if (ready && Glyph_Kit->y + height <= Print_Texture_H && Stack_End - Stack_Cur >= width*height*4)
				{

					Glyph->u1 =(vertex_real_t) Glyph_Kit->x;
					Glyph->v1 =(vertex_real_t) Glyph_Kit->y;
					Glyph->u2 = Glyph->u1 + width;
					Glyph->v2 = Glyph->v1 + height;

					Glyph_Kit->x =(int) Glyph->u2 + 2;

					uint32_t* image =(uint32_t*) Stack_Cur;
					uint8_t* pixels = data;

					for (int y = 0; y < height; ++y)
					{
						for (int x = 0; x < width; ++x)
						{
							*image++ = (uint32_t(pixels[x])<<24) | 0xFFFFFF;
						}
						pixels += pitch;
					}
					for (int x = 0; x < width; ++x)
					{
						*image++ = 0xFFFFFF;
					}

					glTexSubImage2D(GL_TEXTURE_2D, 0, (GLint)Glyph->u1, (GLint)Glyph->v1, width, height+1, GL_RGBA, GL_UNSIGNED_BYTE, Stack_Cur);
					glFlush();
				}
				//FT_Done_Glyph(glyphDesc);
			}
			if (!ready)
			{
				// удалить элемент
				Glyph = 0;
			}
		}
	}
	if (Glyph == 0)
	{
		// удалить элемент
		//Kegel = 0;
	}
	return Glyph != 0;
}


bool Print_Vertex(const vertex_real_t x1, const vertex_real_t y1, const vertex_real_t w, const vertex_real_t h, const vertex_real_t u1 = 1, const vertex_real_t v1 = 1, const vertex_real_t u2 = 1, const vertex_real_t v2 = 1)
{           
	if ( Stack_End - Stack_Cur >= sizeof(Vertex_Data[0])*12 )
	{
		const vertex_real_t x2 = x1 + w;
		const vertex_real_t y2 = y1 + h;
		Vertex_Cur[ 0].x = x1; Vertex_Cur[ 0].y = y1; Vertex_Cur[ 1].x = u1; Vertex_Cur[ 1].y = v1;
		Vertex_Cur[ 2].x = x2; Vertex_Cur[ 2].y = y1; Vertex_Cur[ 3].x = u2; Vertex_Cur[ 3].y = v1;
		Vertex_Cur[ 4].x = x1; Vertex_Cur[ 4].y = y2; Vertex_Cur[ 5].x = u1; Vertex_Cur[ 5].y = v2;
		Vertex_Cur[ 6].x = x1; Vertex_Cur[ 6].y = y2; Vertex_Cur[ 7].x = u1; Vertex_Cur[ 7].y = v2;
		Vertex_Cur[ 8].x = x2; Vertex_Cur[ 8].y = y1; Vertex_Cur[ 9].x = u2; Vertex_Cur[ 9].y = v1;
		Vertex_Cur[10].x = x2; Vertex_Cur[10].y = y2; Vertex_Cur[11].x = u2; Vertex_Cur[11].y = v2;
		Vertex_Cur += 12;
		return 1;
	}
	return 0;
}

void Print(const wchar_t* string)
{
	if (Opacity <= 0) return;
	
	Face = 0;
	if ( Database(&Face_List, &Face, Font) )
	{
		if (Font_Face(Font) == 0)
		{
			// удалить элемент
			Face = 0;
		}
	}
	if (Face)
	{
		const r_t s = Font_H*Raster.y;
		Glyph_H = Min( (uint16_t(s+0.5)/Glyph_Grid + 1)*Glyph_Grid, 256);
		float w = 0;
		float h = 1;
		float x = 0;
		float y = h - (Face->underline + Face->thickness/2);
		wchar_t prevChar = 0;
		Vertex_Data = Vertex_Cur;
		for (const wchar_t* p = string;; p++)
		{
			if (p[0] == ' ')
			{
				x += Face->w;
			}
			else
			if (p[0] == '\t')
			{
				x += Face->w*4;
			}
			else
			if (p[0] == 0 || p[0] == '\n')
			{
				if (Underlined)
				{
					Print_Vertex(0, y + Face->underline - Face->thickness/2, x, Face->thickness);	
				}
				if (Strikethrough)
				{
					Print_Vertex(0, y + Face->strikethrough - Face->thickness/2, x, Face->thickness);
				}

				High(w, x);

				if (p[0] == '\n')
				{
					h += Face->h;
					y += Face->h;
					x = 0;
				}
				else
				{
					break;
				}
			}
			else
			{
				if (Print_Glyph(p[0]) == 0)
				{
					break;
				}

				if (Print_Vertex(x + Glyph->l, y + Glyph->t, Glyph->w, Glyph->h, Glyph->u1, Glyph->v1, Glyph->u2, Glyph->v2) == 0)
				{
					break;
				}

				x += Print_Kerning(p[0], p[1]);
			}
		}

		if (w)
		{
			if (Print_Texture)
			{
				glMatrixMode(GL_TEXTURE);
				glLoadIdentity();
				glScalef(1.f/float(Print_Texture_W), 1.f/float(Print_Texture_H), 1);

				glEnable(GL_TEXTURE_2D);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			}
			else
			{
				glDisable(GL_TEXTURE_2D);
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			}
					
			Cover_Matrix();
			v2_t p = XY*Raster;
			glTranslated(p.x,p.y,0);
			glRotated(Angle, 0, 0, 1);
			glScaled(s, s, 1);
			glTranslated(-Pin.x*w,-Pin.y*h,0);

			//glColor4d(Color.r,Color.g,Color.b,Opacity);			
			glColor();
			glDisableClientState(GL_COLOR_ARRAY);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glVertexPointer(2, GL_Type(Vertex_Data), sizeof(Vertex_Data[0])*2, Vertex_Data);
			glTexCoordPointer(2, GL_Type(Vertex_Data), sizeof(Vertex_Data[0])*2, &Vertex_Data[1]);
			glDrawArrays(GL_TRIANGLES, 0, (Vertex_Cur - Vertex_Data)/2);
		}

		Stack_Set(Vertex_Data);
		Vertex_Data = 0;

		W1 = w*s/Raster.x;
		H1 = h*s/Raster.y;
	}
}