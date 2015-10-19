#ifndef __FLY_BUTTON_H
#define __FLY_BUTTON_H

#include <SDL_scancode.h>

typedef enum
{
	Key_A = SDL_SCANCODE_A,
	Key_B = SDL_SCANCODE_B,
	Key_C = SDL_SCANCODE_C,
	Key_D = SDL_SCANCODE_D,
	Key_E = SDL_SCANCODE_E,
	Key_F = SDL_SCANCODE_F,
    Key_G = SDL_SCANCODE_G,
	Key_H = SDL_SCANCODE_H,
	Key_I = SDL_SCANCODE_I,
    Key_J = SDL_SCANCODE_J,
    Key_K = SDL_SCANCODE_K,
    Key_L = SDL_SCANCODE_L,
    Key_M = SDL_SCANCODE_M,
    Key_N = SDL_SCANCODE_N,
    Key_O = SDL_SCANCODE_O,
    Key_P = SDL_SCANCODE_P,
    Key_Q = SDL_SCANCODE_Q,
    Key_R = SDL_SCANCODE_R,
    Key_S = SDL_SCANCODE_S,
    Key_T = SDL_SCANCODE_T,
    Key_U = SDL_SCANCODE_U,
    Key_V = SDL_SCANCODE_V,
    Key_W = SDL_SCANCODE_W,
    Key_X = SDL_SCANCODE_X,
    Key_Y = SDL_SCANCODE_Y,
    Key_Z = SDL_SCANCODE_Z,

    Key_1 = SDL_SCANCODE_1,
    Key_2 = SDL_SCANCODE_2,
    Key_3 = SDL_SCANCODE_3,
    Key_4 = SDL_SCANCODE_4,
    Key_5 = SDL_SCANCODE_5,
    Key_6 = SDL_SCANCODE_6,
    Key_7 = SDL_SCANCODE_7,
    Key_8 = SDL_SCANCODE_8,
    Key_9 = SDL_SCANCODE_9,
    Key_0 = SDL_SCANCODE_0,

    Key_Enter = SDL_SCANCODE_RETURN,
    Key_Escape =  SDL_SCANCODE_ESCAPE,
    Key_Backspace = SDL_SCANCODE_BACKSPACE,
    Key_Tab = SDL_SCANCODE_TAB,
    Key_Space = SDL_SCANCODE_SPACE,

    Key_Minus = SDL_SCANCODE_MINUS,
    Key_Equals = SDL_SCANCODE_EQUALS,
    Key_Left_Bracket = SDL_SCANCODE_LEFTBRACKET,
    Key_Right_Braket = SDL_SCANCODE_RIGHTBRACKET,
    Key_Back_Slash = SDL_SCANCODE_BACKSLASH, // < Located at the lower left of the return
                                
    Key_Nonushash = SDL_SCANCODE_NONUSHASH, //< ISO USB keyboards actually use this code
                                  
    Key_Semicolon = SDL_SCANCODE_SEMICOLON,
    Key_Apostrophe = SDL_SCANCODE_APOSTROPHE,
    Key_Grave = SDL_SCANCODE_GRAVE, //< Located in the top left corner (on both ANSI
                              
    Key_Comma = SDL_SCANCODE_COMMA,
    Key_Period = SDL_SCANCODE_PERIOD,
    Key_Slash = SDL_SCANCODE_SLASH,

    Key_Capslock = SDL_SCANCODE_CAPSLOCK,

    Key_F1 = SDL_SCANCODE_F1,
    Key_F2 = SDL_SCANCODE_F2,
    Key_F3 = SDL_SCANCODE_F3,
    Key_F4 = SDL_SCANCODE_F4,
    Key_F5 = SDL_SCANCODE_F5,
    Key_F6 = SDL_SCANCODE_F6,
    Key_F7 = SDL_SCANCODE_F7,
    Key_F8 = SDL_SCANCODE_F8,
    Key_F9 = SDL_SCANCODE_F9,
    Key_F10 = SDL_SCANCODE_F10,
	Key_F11 = SDL_SCANCODE_F11,
    Key_F12 = SDL_SCANCODE_F12,

    Key_Print_Screen = SDL_SCANCODE_PRINTSCREEN,
    Key_Scroll_Lock = SDL_SCANCODE_SCROLLLOCK,
    Key_Pause = SDL_SCANCODE_PAUSE,
    Key_Insert = SDL_SCANCODE_INSERT, 

    Key_Home = SDL_SCANCODE_HOME,
    Key_Page_Up = SDL_SCANCODE_PAGEUP,
    Key_Delete = SDL_SCANCODE_DELETE,
    Key_End = SDL_SCANCODE_END,
    Key_Page_Down = SDL_SCANCODE_PAGEDOWN,
    Key_Right = SDL_SCANCODE_RIGHT,
    Key_Left = SDL_SCANCODE_LEFT,
    Key_Down = SDL_SCANCODE_DOWN,
    Key_Up = SDL_SCANCODE_UP,

    Key_Numlock = SDL_SCANCODE_NUMLOCKCLEAR, /**< num lock on PC, clear on Mac keyboards*/

    Numpad_Divide = SDL_SCANCODE_KP_DIVIDE,
    Numpad_Multiply = SDL_SCANCODE_KP_MULTIPLY,
    Numpad_Minus = SDL_SCANCODE_KP_MINUS,
    Numpad_Plus = SDL_SCANCODE_KP_PLUS,
    Numpad_Enter = SDL_SCANCODE_KP_ENTER,
    Numpad_1 = SDL_SCANCODE_KP_1,
    Numpad_2 = SDL_SCANCODE_KP_2,
    Numpad_3 = SDL_SCANCODE_KP_3,
    Numpad_4 = SDL_SCANCODE_KP_4,
    Numpad_5 = SDL_SCANCODE_KP_5,
    Numpad_6 = SDL_SCANCODE_KP_6,
    Numpad_7 = SDL_SCANCODE_KP_7,
    Numpad_8 = SDL_SCANCODE_KP_8,
    Numpad_9 = SDL_SCANCODE_KP_9,
    Numpad_0 = SDL_SCANCODE_KP_0,
    Numpad_Period = SDL_SCANCODE_KP_PERIOD,

    Key_Nonus_Back_Slash = SDL_SCANCODE_NONUSBACKSLASH, //< This is the additional key that ISO
                                        
    Key_Application = SDL_SCANCODE_APPLICATION, /**< windows contextual menu, compose */
    Key_Power = SDL_SCANCODE_POWER, //< The USB document says this is a status flag,
                              
    Numpad_Equals = SDL_SCANCODE_KP_EQUALS,
    Key_F13 = SDL_SCANCODE_F13,
    Key_F14 = SDL_SCANCODE_F14,
    Key_F15 = SDL_SCANCODE_F15,
    Key_F16 = SDL_SCANCODE_F16,
    Key_F17 = SDL_SCANCODE_F17,
    Key_F18 = SDL_SCANCODE_F18,
    Key_F19 = SDL_SCANCODE_F19,
    Key_F20 = SDL_SCANCODE_F20,
    Key_F21 = SDL_SCANCODE_F21,
    Key_F22 = SDL_SCANCODE_F22,
    Key_F23 = SDL_SCANCODE_F23,
    Key_F24 = SDL_SCANCODE_F24,
    Key_Execute = SDL_SCANCODE_EXECUTE,
    Key_Help = SDL_SCANCODE_HELP,
    Key_Menu = SDL_SCANCODE_MENU,
    Key_Select = SDL_SCANCODE_SELECT,
    Key_Stop = SDL_SCANCODE_STOP,
    Key_Redo = SDL_SCANCODE_AGAIN,   /**< redo */
    Key_Undo = SDL_SCANCODE_UNDO,
    Key_Cut = SDL_SCANCODE_CUT,
    Key_Copy = SDL_SCANCODE_COPY,
    Key_Paste = SDL_SCANCODE_PASTE,
    Key_Find = SDL_SCANCODE_FIND,
    Key_Mute = SDL_SCANCODE_MUTE,
    Key_Volue_Up = SDL_SCANCODE_VOLUMEUP,
    Key_Volume_Down = SDL_SCANCODE_VOLUMEDOWN,
/* not sure whether there's a reason to enable these */
/*     SDL_SCANCODE_LOCKINGCAPSLOCK = 130,  */
/*     SDL_SCANCODE_LOCKINGNUMLOCK = 131, */
/*     SDL_SCANCODE_LOCKINGSCROLLLOCK = 132, */
    Numpad_Comma = SDL_SCANCODE_KP_COMMA,
    Numpad_Equals_As_400 = SDL_SCANCODE_KP_EQUALSAS400,

    Key_International1 = SDL_SCANCODE_INTERNATIONAL1,
    Key_International2 = SDL_SCANCODE_INTERNATIONAL2,
    Key_International3 = SDL_SCANCODE_INTERNATIONAL3,
    Key_International4 = SDL_SCANCODE_INTERNATIONAL4,
    Key_International5 = SDL_SCANCODE_INTERNATIONAL5,
    Key_International6 = SDL_SCANCODE_INTERNATIONAL6,
    Key_International7 = SDL_SCANCODE_INTERNATIONAL7,
    Key_International8 = SDL_SCANCODE_INTERNATIONAL8,
    Key_International9 = SDL_SCANCODE_INTERNATIONAL9,
    Key_Lang1 = SDL_SCANCODE_LANG1, /**< Hangul/English toggle */
    Key_Lang2 = SDL_SCANCODE_LANG2, /**< Hanja conversion */
    Key_Lang3 = SDL_SCANCODE_LANG3, /**< Katakana */
    Key_Lang4 = SDL_SCANCODE_LANG4, /**< Hiragana */
    Key_Lang5 = SDL_SCANCODE_LANG5, /**< Zenkaku/Hankaku */
    Key_Lang6 = SDL_SCANCODE_LANG6, /**< reserved */
    Key_Lang7 = SDL_SCANCODE_LANG7, /**< reserved */
    Key_Lang8 = SDL_SCANCODE_LANG8, /**< reserved */
    Key_Lang9 = SDL_SCANCODE_LANG9, /**< reserved */

    Key_Alterase = SDL_SCANCODE_ALTERASE, /**< Erase-Eaze */
    Key_Sysreq = SDL_SCANCODE_SYSREQ,
    Key_Cancel = SDL_SCANCODE_CANCEL,
    Key_Clear = SDL_SCANCODE_CLEAR,
    Key_Prior = SDL_SCANCODE_PRIOR,
    Key_Return = SDL_SCANCODE_RETURN2,
    Key_Separator = SDL_SCANCODE_SEPARATOR,
    Key_Out = SDL_SCANCODE_OUT,
    Key_Oper = SDL_SCANCODE_OPER,
    Key_Clear_Again = SDL_SCANCODE_CLEARAGAIN,
    Key_Crsel = SDL_SCANCODE_CRSEL,
    Key_Exsel = SDL_SCANCODE_EXSEL,

    Numpad_00 = SDL_SCANCODE_KP_00,
    Numpad_000 = SDL_SCANCODE_KP_000,
    Numpad_Thousands_Separator = SDL_SCANCODE_THOUSANDSSEPARATOR,
    Numpad_Decimal_Separator = SDL_SCANCODE_DECIMALSEPARATOR,
    Numpad_Currency_Unit = SDL_SCANCODE_CURRENCYUNIT,
    Numpad_Cyrrency_Subunit = SDL_SCANCODE_CURRENCYSUBUNIT,
    Numpad_Left_Paren = SDL_SCANCODE_KP_LEFTPAREN,
    Numpad_Right_Paren = SDL_SCANCODE_KP_RIGHTPAREN,
    Numpad_Left_Brace = SDL_SCANCODE_KP_LEFTBRACE,
    Numpad_Right_Brace = SDL_SCANCODE_KP_RIGHTBRACE,
    Numpad_Tab = SDL_SCANCODE_KP_TAB,
    Numpad_Backspace = SDL_SCANCODE_KP_BACKSPACE,
    Numpad_A = SDL_SCANCODE_KP_A,
    Numpad_B = SDL_SCANCODE_KP_B,
    Numpad_C = SDL_SCANCODE_KP_C,
    Numpad_D = SDL_SCANCODE_KP_D,
    Numpad_E = SDL_SCANCODE_KP_E,
    Numpad_F = SDL_SCANCODE_KP_F,
    Numpad_Xor = SDL_SCANCODE_KP_XOR,
    Numpad_Power = SDL_SCANCODE_KP_POWER,
    Numpad_Percent = SDL_SCANCODE_KP_PERCENT,
    Numpad_Less = SDL_SCANCODE_KP_LESS,
    Numpad_Greater = SDL_SCANCODE_KP_GREATER,
    Numpad_Ampersand = SDL_SCANCODE_KP_AMPERSAND,
    Numpad_Double_Ampersand = SDL_SCANCODE_KP_DBLAMPERSAND,
    Numpad_Vertical_Bar = SDL_SCANCODE_KP_VERTICALBAR,
    Numpad_Double_Vertical_Bar = SDL_SCANCODE_KP_DBLVERTICALBAR,
    Numpad_Colon = SDL_SCANCODE_KP_COLON,
    Numpad_Hash = SDL_SCANCODE_KP_HASH,
    Numpad_Space = SDL_SCANCODE_KP_SPACE,
    Numpad_At = SDL_SCANCODE_KP_AT,
    Numpad_Exclam = SDL_SCANCODE_KP_EXCLAM,
    Numpad_Memory_Store = SDL_SCANCODE_KP_MEMSTORE,
    Numpad_Memory_Recall = SDL_SCANCODE_KP_MEMRECALL,
    Numpad_Memory_Clear = SDL_SCANCODE_KP_MEMCLEAR,
    Numpad_Memory_Add = SDL_SCANCODE_KP_MEMADD,
    Numpad_Memory_Sub = SDL_SCANCODE_KP_MEMSUBTRACT,
    Numpad_Memory_Mul = SDL_SCANCODE_KP_MEMMULTIPLY,
    Numpad_Memory_Div = SDL_SCANCODE_KP_MEMDIVIDE,
    Numpad_Plus_Minus = SDL_SCANCODE_KP_PLUSMINUS,
    Numpad_Clear = SDL_SCANCODE_KP_CLEAR,
    Numpad_Clear_Entry = SDL_SCANCODE_KP_CLEARENTRY,
    Numpad_Bin = SDL_SCANCODE_KP_BINARY,
    Numpad_Oct = SDL_SCANCODE_KP_OCTAL,
    Numpad_Dec = SDL_SCANCODE_KP_DECIMAL,
    Numpad_Hex = SDL_SCANCODE_KP_HEXADECIMAL,

    Key_Left_Ctrl = SDL_SCANCODE_LCTRL,
    Key_Left_Shift = SDL_SCANCODE_LSHIFT,
    Key_Left_Alt = SDL_SCANCODE_LALT, /**< alt, option */
    Key_Left_Win = SDL_SCANCODE_LGUI, /**< windows, command (apple), meta */
    Key_Right_Ctrl = SDL_SCANCODE_RCTRL,
    Key_Right_Shift = SDL_SCANCODE_RSHIFT,
    Key_Right_Alt = SDL_SCANCODE_RALT, /**< alt gr, option */
    Key_Right_Win = SDL_SCANCODE_RGUI, /**< windows, command (apple), meta */

    Key_Mode = SDL_SCANCODE_MODE,    //*< I'm not sure if this is really not covered
            

    Key_Audio_Next = SDL_SCANCODE_AUDIONEXT,
    Key_Audio_Prev = SDL_SCANCODE_AUDIOPREV,
    Key_Audio_Stop = SDL_SCANCODE_AUDIOSTOP,
    Key_Audio_Play = SDL_SCANCODE_AUDIOPLAY,
    Key_Audio_Mute = SDL_SCANCODE_AUDIOMUTE,
    Key_Media_Select = SDL_SCANCODE_MEDIASELECT,

	Shortcut_WWW = SDL_SCANCODE_WWW,
    Shortcut_Mail = SDL_SCANCODE_MAIL,
    Shortcut_Calculator = SDL_SCANCODE_CALCULATOR,
    Shortcut_Computer = SDL_SCANCODE_COMPUTER,
    Shortcut_Search = SDL_SCANCODE_AC_SEARCH,
    Shortcut_Home = SDL_SCANCODE_AC_HOME,
	Shortcut_Back = SDL_SCANCODE_AC_BACK,
    Shortcut_Forward = SDL_SCANCODE_AC_FORWARD,
    Shortcut_Stop = SDL_SCANCODE_AC_STOP,
    Shortcut_Refresh = SDL_SCANCODE_AC_REFRESH,
    Shortcut_Bookmarks = SDL_SCANCODE_AC_BOOKMARKS,

    Key_Brightness_Down = SDL_SCANCODE_BRIGHTNESSDOWN,
    Key_Brightness_Up = SDL_SCANCODE_BRIGHTNESSUP,
    Key_Display_Switch = SDL_SCANCODE_DISPLAYSWITCH, //< display mirroring/dual display
                                         
    Key_Keyboard_Lum_Toggle = SDL_SCANCODE_KBDILLUMTOGGLE,
    Key_Keyboard_Lum_Down = SDL_SCANCODE_KBDILLUMDOWN,
    Key_Keyboard_DILLUMUP = SDL_SCANCODE_KBDILLUMUP,
    Key_Eject = SDL_SCANCODE_EJECT,
    Key_Sleep = SDL_SCANCODE_SLEEP,

    Key_App1 = SDL_SCANCODE_APP1,
    Key_App2 = SDL_SCANCODE_APP2,

	Keys,

	Mouse_First = Keys, 
	Mouse_Left = Mouse_First,
	Mouse_Middle,
	Mouse_Right,
	Mouse_X1,
	Mouse_X2,
	Mouse_Last,
	Mouse_Buttons = Mouse_Last - Mouse_First,

	Buttons = Mouse_Last
}
button_t;



#endif