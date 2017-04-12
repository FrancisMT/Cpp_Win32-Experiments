#include <Windows.h>	/* The standard "windows.h" inclusion */

/* Create nice looking controls */
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

int WINAPI WinMain(HINSTANCE hInstance,		/* A handle to the current instance of the application. */
	HINSTANCE hPrevInstance,	/* A handle to the previous instance of the application. */
	LPSTR lpCmdLine,			/* The command line for the application, excluding the program name. */
	int nCmdShow)				/* Controls how the window is to be shown. */
{


	auto lp_text = reinterpret_cast<LPWSTR>("Hello, Windows API!");
	auto lp_cation = reinterpret_cast<LPWSTR>("Hello");


	/* Call to the MessageBox function */
	MessageBox(nullptr, lp_text, lp_cation, MB_OK | MB_ICONINFORMATION);

	/* WinMain returns 0 if we exit before we enter message loop, more on that to come */
	return 0;
}