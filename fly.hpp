#ifndef __FLY_HPP
#define __FLY_HPP

#include "flycase.hpp"
#include "flylib.hpp"
#include "flymath.hpp"
#include "flypicture.hpp"
#include "vector.hpp"
#include "button.h"
#include <sstream>
#include <time.h>


struct sound_s;
extern sound_s* Sound_List;
void Sound(char* name);

typedef double r_t;
typedef vector2_c<r_t> v2_t;
typedef vector3_c<r_t> v3_t;

extern bool Fly;

struct rect_s
{
	v2_t pos;
	v2_t size;
};

struct zone_s
{
	bool		visible;
	int			matrix;
	v2_t		raster;
	rect_s		rect;
	v2_t		pin;
	//v2_t		scale;
	r_t			angle;

	v2_t		screen;

	v2_t		mouse;
	v2_t		mouse_move;

	v2_t		finger;
	v2_t		finger_move;
};
extern zone_s	Zone;
static bool&	Visible = Zone.visible;
static v2_t&	Raster = Zone.raster;
static rect_s&		Rect = Zone.rect;
static v2_t&	XY = Rect.pos;
static v2_t&	WH = Rect.size;
static r_t&		X = XY.x;
static r_t&		Y = XY.y;
static r_t&		W = WH.x;
static r_t&		H = WH.y;
static v2_t&	Pin = Zone.pin;
static r_t&		Pin_X = Pin.x;
static r_t&		Pin_Y = Pin.y;
static r_t&		Angle = Zone.angle;
static v2_t&	Mouse  = Zone.mouse;
static v2_t&		Mouse_Move = Zone.mouse_move;
static v2_t&		Finger = Zone.finger;
static v2_t&		Finger_Move = Zone.finger_move;


struct zone_c
{
	zone_s	data;
	bool	run;

	zone_c();

	
	void end()
	{
		Zone = data;
		run = 0;
	}
};

#define zone for (zone_c temp; temp.run; temp.end())

struct fly_ui_s
{
	v2_t	resolution;
	
	r_t		wheel;

	v2_t	wh1;

	uint8_t		touch;

	uint8_t*	picture_Data;
	int			picture_X;
	int			picture_Y;
	
};
extern fly_ui_s		Fly_UI;
static r_t&		Mouse_Wheel = Fly_UI.wheel;
static v2_t&	Resolution = Fly_UI.resolution;
static v2_t&	WH1 = Fly_UI.wh1;
static r_t&		W1 = WH1.x;
static r_t&		H1 = WH1.y;
static uint8_t&		Touch = Fly_UI.touch;
static uint8_t*&	Picture_Data = Fly_UI.picture_Data;
static int&		Picture_X = Fly_UI.picture_X;
static int&		Picture_Y = Fly_UI.picture_Y;

extern r_t		Thick;

typedef r_t color_part_t;
//typedef vector3_c<color_part_t> color_t;
struct color_t : vector3_c<color_part_t>
{
	color_t(int v = 0) : vector3_c<color_part_t>
	(
		color_part_t( (v>>16)&0xFF )/255.0, 
		color_part_t( (v>>8)&0xFF )/255.0,
		color_part_t( (v>>0)&0xFF )/255.0
	)
	{}
	color_t(color_part_t r, color_part_t g, color_part_t b) : vector3_c<color_part_t>(r, g, b) {}
};
extern color_t	Color;
inline color_t	Red(double a)	{ return color_t((color_part_t)a,0,0); }
inline color_t	Green(double a)	{ return color_t(0,(color_part_t)a,0); }
inline color_t	Blue(double a)	{ return color_t(0,0,(color_part_t)a); }
inline color_t	White(double a)	{ return color_t((color_part_t)a,(color_part_t)a,(color_part_t)a); }
//inline glass_t	Alpha(double a)	{ return glass_t(0,0,0,(color_part_t)a); }
extern double	Opacity;

inline void WH_Quad()
{
	r_t x = Raster.x;
	r_t y = Raster.y;
	if (abs(x) >= abs(y))
	{
		W *= y/x;
	}
	else
	{
		H *= x/y;
	}
}

inline v2_t WH_Quad(r_t wh)
{
	WH  = wh;
	WH_Quad();
	return WH;
}



void Fill();
void Box();
void Triangle();
void Circle();
inline void Circle(r_t d)
{
	WH = d;
	WH_Quad();
	Circle();
}
void Pie(r_t angle);

void Vertex(r_t x, r_t y);
void Zigzag();
void Polygon();
void Diagonal();

void Line();
void Curve(r_t steps);

struct texture_s
{
	texture_s*		next;
	unsigned		core;
	v2_t			pixels;
	int				use;
	v2_t			xy;
	v2_t			wh;
};

extern texture_s* Texture_Load_List;
extern texture_s* Texture;

//bool Texture_Open(GLuint* id,  GLsizei w, GLsizei h);

inline v2_t Size_Of(texture_s* texture)
{
	if (texture)
	{
		return texture->pixels/Raster;
	}
	return 0;
}



void Layer(const char_t* name);

bool Picture_Load(char_t* name);

//texture_s* Picture();
//texture_s* Picture(char_t* name, texture_s** list = &Texture_Load_List);
extern picture_c Picture;
void Paint(char_t* name);
void Paint();

extern char*	Font;
extern r_t		Font_H;
extern bool		Underlined;
extern bool		Strikethrough;
void Print(const wchar_t* string);
void Print();

inline void Print()
{
	Text << '\0';
	Print(Text.str().c_str());
	Text_New();
}

template<class type_a> 
inline void Print(type_a a)
{
	Text << a;
	Print();
}

bool Button_On(button_t code);
bool Button_To_On(button_t code);
bool Button_To_Off(button_t code);




extern clock_t	Clock;
extern clock_t	Spell;

typedef double second_t;
extern second_t T;
extern second_t Timer;




inline void Site_Rise()
{
	XY = 0;
	WH = 1;
	Pin = 0;
	Angle = 0;
}

int Fly_Start(entry_t entry);


inline void Text_Time(r_t sec)
{
	if (sec == 0)
	{
		Text << L"0";
	}
	else
	{
		r_t	min = floor(sec/60); sec -= 60*min;
		r_t hour = floor(min/60); min -= 60*hour;
		r_t day  = floor(hour/24); hour -= 24*day;

		if (day)
		{
			Text << day << L" ä ";
		}
		if (hour)
		{
			Text << hour << L" ÷ ";
		}
		if (min && day == 0)
		{
			Text << min << L" ì ";
		}
		if (sec && hour == 0 && day == 0)
		{
			Text << sec << L" c";
		}
	}
}

inline v2_t Projection(v2_t vector, r_t angle)
{
	const double pi = 3.14159265358979323846;
	double c = cos(angle*pi/180.0);
	double s = sin(angle*pi/180.0);
	return v2_t
	(
		vector.x*c + vector.y*s,
		vector.y*c - vector.x*s
	);
}

inline bool Insite(v2_t p, v2_t wh = WH)
{
	p = Projection((p - XY)*Raster, Angle);
	v2_t s = wh*Raster;
	p += Pin*s;
	return p.x >= 0 && p.y >= 0 && p.x <= s.x && p.y <= s.y;
}

inline bool Insite(r_t x, r_t y, v2_t wh = WH)
{
	return Insite(v2_t(x, y), wh);
}

#endif