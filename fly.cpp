#define SDL_MAIN_HANDLED
#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_ttf.h>

//#include "data.hpp"
//#include "fly.hpp"
#include "flyopengl.hpp"

#include <SDL_mixer.h>
#include "flydb.hpp"

struct sound_s
{
	sound_s*		next;
	Mix_Chunk*		core;
};

sound_s* Sound_List = 0;

void Sound(char* name)
{
	sound_s* sound = 0;
	if ( Database(&Sound_List, &sound, name) )
	{
		sound->core = Mix_LoadWAV(name);
		if (sound->core == 0)
		{
			// удалить из списка
			sound = 0;
		}
	}
	if (sound)
	{
		Mix_PlayChannel(-1, sound->core, 0);
	}
}

picture_c Picture;

text_t Text;

text_t& Text_New()
{
	Text.seekp(0);
	return Text;
}



clock_t		Clock;
clock_t		Spell = 2;
second_t	T;
second_t	Timer = 0;

fly_ui_s		Fly_UI;


static uint8_t Button[Buttons] = { 0 };

bool Button_On(button_t code)
{
	return Button[code] & 1;
}

bool Button_To_On(button_t code)
{
	return Button[code] == 1;
}

bool Button_To_Off(button_t code)
{
	return Button[code] == 2;
}

void Button_Set(button_t code, bool state)
{
	Button[code] &= ~1;
	Button[code] |= state ? 1 : 0;
}

SDL_Event Event;

int Event_Mouse_X = 0;
int Event_Mouse_Y = 0;

inline void Event_Mouse()
{
	//Mouse.x = Event.motion.x;
	//Mouse.y = Event.motion.y;
	//Mouse /= Resolution;

	Event_Mouse_X = Event.motion.x;
	Event_Mouse_Y = Event.motion.y;
}


inline void Event_Mouse(uint8_t value)
{
	Event_Mouse();
	Pulse(Button[Mouse_First + Event.button.button - 1], value);
}

bool Fly;

int Fly_Start(entry_t entry)
{
	Entry = entry;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
	//Mix_Chunk *gHigh = Mix_LoadWAV("high.wav");
	//Mix_PlayChannel(-1, gHigh, 3);
	
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_DisplayMode display;
	SDL_GetDesktopDisplayMode(0, &display);
	Resolution.x = display.w;
	Resolution.y = display.h;
	Raster = Resolution;

	// Создаем окно с заголовком "Cube", размером 640х480 и расположенным по центру экрана.
	SDL_Window* window = SDL_CreateWindow("FLY", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, display.w+1, display.h,  SDL_WINDOW_BORDERLESS | SDL_WINDOW_OPENGL);
	//SDL_Window* window = SDL_CreateWindow("FLY", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, display.w+1, display.h,  SDL_WINDOW_RESIZABLE | SDL_WINDOW_BORDERLESS | SDL_WINDOW_OPENGL);
	//SDL_Window* window = SDL_CreateWindow("FLY", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, display.w+1, display.h,  SDL_WINDOW_BORDERLESS | SDL_WINDOW_OPENGL);


	//window = SDL_CreateWindow("Cube", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	
	SDL_GLContext glcontext = SDL_GL_CreateContext(window); // создаем контекст OpenGL

	glInit();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // устанавливаем фоновый цвет на черный
	//glShadeModel(GL_SMOOTH);
	
	//IMG_Init( IMG_INIT_PNG );
	//TTF_Init();

	Clock = SDL_GetTicks();

	Fly = 1;
	for (; Fly; )
	{
		//SDL_Rect rect;
		//SDL_GetWindowSize(window, &rect.w, &rect.h);

		for (; SDL_PollEvent(&Event) != 0; )
		{
			if ( Event.type == SDL_QUIT )
			{
				Fly = 0;
			}
			/*
			else 
			if (Event.type == SDL_KEYDOWN)
			{
				switch (Event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
					quit = true;
					break;
				}
			}
			*/
			else
			if (Event.type == SDL_MOUSEMOTION)
			{
				Event_Mouse();
			}
			else
			if (Event.type == SDL_MOUSEBUTTONDOWN)
			{
				Event_Mouse();
				Pulse(Button[Mouse_First + Event.button.button-1], 1);
				//Button[Mouse_First + Event.button.button-1] |= 1;
			}
			else
			if (Event.type == SDL_MOUSEBUTTONUP)
			{
				Event_Mouse();
				Pulse(Button[Mouse_First + Event.button.button-1], 0);
				//Button[Mouse_First + Event.button.button-1] &= ~1;
			}
			/*
			else
			if (Event.type == SDL_KEYDOWN)
			{
				Button[Event.key.keysym.scancode] |= 1;
			}
			else
			if (Event.type == SDL_KEYUP)
			{
				Button[Event.key.keysym.scancode] &= ~1;
			}
			*/
		}

		clock_t time = clock()*1000/CLOCKS_PER_SEC;
		time_t time_delta = time - Clock;
		if (time_delta >= Spell)
		{
			T = second_t(time_delta)*1e-3;
			Timer += T;
			Clock = time;

			{
				int keys;
				const uint8_t* key = SDL_GetKeyboardState(&keys);
				Low(keys, Keys);
				for (int i = 0; i < keys; i++)
				{
					//Button[i] &= ~1;
					//Button[i] |= key[i] ? 1 : 0;
					Pulse(Button[i], key[i]);
				}
			}
			
			
			//SDL_GetMouseState(&x, &y);
			v2_t mouse_leave = Mouse;
			Mouse.x = Event_Mouse_X;
			Mouse.y = Event_Mouse_Y;
			Mouse /= Raster;
			Mouse_Move = Mouse - mouse_leave;

			glClear(GL_COLOR_BUFFER_BIT);

			XY = 0;
			WH = 1;
			Pin = 0;
			Angle = 0;

			Color = White(1);
			Opacity = 1;

			Thick = 1;

			Stack_Cur = Stack_Data;
			Zone.raster = Resolution;
			Zone.matrix = 1;

			Entry();

			Mouse_Wheel = 0;

			glFlush();
			SDL_GL_SwapWindow(window);

			for (int i = Mouse_First; i < Mouse_Last; i++) Pulse(Button[i], Button[i]&1);

			Picture.reset();

			Sleep(1);
		}
	}

	return 0;
}