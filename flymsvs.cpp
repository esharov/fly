#pragma comment(lib, "sdl2.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "SDL2_mixer.lib")


#pragma comment(linker, "/NODEFAULTLIB:libcmt.lib")
#pragma comment(linker, "/NODEFAULTLIB:odbc32.lib")
#pragma comment(linker, "/NODEFAULTLIB:odbc32.lib")
#pragma comment(linker, "/NODEFAULTLIB:oleaut32.lib")
#pragma comment(linker, "/NODEFAULTLIB:shell32.lib")
#pragma comment(linker, "/NODEFAULTLIB:advapi32.lib")
#pragma comment(linker, "/NODEFAULTLIB:comdlg32.lib")
#pragma comment(linker, "/NODEFAULTLIB:winspool.lib")
#pragma comment(linker, "/NODEFAULTLIB:gdi32.lib")
#pragma comment(linker, "/NODEFAULTLIB:user32.lib")
/*
ole32.lib - WIC
uuid.lib - WIC
*/


int main(); 


int __stdcall wWinMain
(
	void* hInstance, 
	void* hPrevInstance, 
	wchar_t*	  lpCmdLine, 
	int nCmdShow
)
{
	return main();
}