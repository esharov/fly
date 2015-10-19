#include "flyopengl.hpp"
#include "flydb.hpp"
#include "flypicture.hpp"

texture_s* Texture_Load_List;
texture_s* Texture;


bool picture_c::operator() (const char_t* name, texture_s** list)
{
	reset();
	Texture = 0;
	if ( Database(list, &Texture, name) )
	{
		if ( load(name) )
		{
			Texture->pixels.x = w;
			Texture->pixels.y = h;
		}
	}
	if (WH == 0)
	{
		WH = Size_Of(Texture);
	}
	return data != 0;
}


uint8_t* Picture_Load(char_t* name, int* pw, int* ph);

bool Picture_Load(char_t* name)
{
	Picture_Data = Picture_Load(name, &Picture_X, &Picture_Y);
	return Picture_Data != 0;
}

/*
texture_s* Picture()
{
	if (Texture)
	{
		if (Picture_Data)
		{
			Texture->pixels.x = Picture_X;
			Texture->pixels.y = Picture_Y;
			glGenTextures(1, &Texture->core);
			glBindTexture(GL_TEXTURE_2D, Texture->core);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Picture_X, Picture_Y, 0, GL_RGBA, GL_UNSIGNED_BYTE, Picture_Data);
			glFlush();
		}
	}
	if (WH == 0)
	{
		WH = Size_Of(Texture);
	}
	return Texture;
}
*/

/*
texture_s* Picture(char_t* name, texture_s** list)
{
	Texture = 0;
	if ( Database(list, &Texture, name) )
	{
		int w, h;
		uint8_t* data = Picture_Load(name, &w, &h);
		if (data)
		{
			Texture->pixels.x = w;
			Texture->pixels.y = h;
			glGenTextures(1, &Texture->core);
			glBindTexture(GL_TEXTURE_2D, Texture->core);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glFlush();
		}
	}
	if (WH == 0)
	{
		WH = Size_Of(Texture);
	}
	return Texture;
}
*/

void Paint()
{
	if (Texture)
	{
		if (Texture->core == 0)
		{
			glGenTextures(1, &Texture->core);
			glBindTexture(GL_TEXTURE_2D, Texture->core);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Picture.w, Picture.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, Picture.data);
			
			glFlush();
		}

		glBindTexture(GL_TEXTURE_2D, Texture->core);
		glMatrixMode(GL_TEXTURE);
		glLoadIdentity();

		Fly_Matrix_Set();
	
		//glColor4d(Color.r,Color.g,Color.b,Opacity);
		glColor4d(1,1,1,Opacity);

		glEnable(GL_TEXTURE_2D);
		glDisableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, Square_VBO);
		glVertexPointer(2, GL_FLOAT, 0, NULL);
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	}
}

void Paint(char_t* name)
{
	Picture(name);
	Paint();
}


void Layer(const char_t* name)
{
	if ( Picture(name) )
	{
		int t;
		int h;
		int l;
		int w;
		bool go = 1;
		for (int y = 0; y < Picture.h && go; y++)
		{
			for (int x = 0; x < Picture.w; x++)
			{
				if (Picture[y][x].part.alpha > 64)
				{
					t = y;
					go = 0;
					break;
				}
			}
		}


		go = 1;
		for (int y = Picture.h-1; y > t && go; y--)
		{
			for (int x = 0; x < Picture.w; x++)
			{
				if (Picture[y][x].part.alpha > 64)
				{
					h = y - t;
					go = 0;
					break;
				}
			}
		}

		go = 1;
		for (int  x = 0; x < Picture.w && go; x++)
		{
			for (int y = t; y < t + h; y++)
			{
				if (Picture[y][x].part.alpha > 64)
				{

					l = x;
					go = 0;
					break; 
				}
			}
		}

		go = 1;
		for (int  x = Picture.w-1; x > l && go; x--)
		{
			for (int y = t; y < t + h; y++)
			{
				if (Picture[y][x].part.alpha > 64)
				{

					w = x - l;
					go = 0;
					break; 
				}
			}
		}

		if (w != Picture.w || h != Picture.h)
		{
			rgba_s* p = Picture[0];
			for (int y = t; y < t + h; y++)
			{
				for (int x = l; x < l + w; x++)
				{
					*p++ = Picture[y][x];
				}
			}

			Texture->xy.x = r_t(l)/r_t(Picture.w);
			Texture->xy.y = r_t(t)/r_t(Picture.h);

			Texture->wh.x = r_t(w)/r_t(Picture.w);
			Texture->wh.y = r_t(h)/r_t(Picture.h);

			Picture.w = w;
			Picture.h = h;
		}
	}
	if (Texture)
	{
		XY = Texture->xy;
		WH = Texture->wh;
	}
}