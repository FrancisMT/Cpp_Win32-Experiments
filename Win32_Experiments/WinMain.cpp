#include <Windows.h>	/* The standard "windows.h" inclusion */
#include <iostream>

/* Create nice looking controls */
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

/* Name of our class and the title */
const auto clsName = reinterpret_cast<LPCWSTR>("WinAPI");
auto title = reinterpret_cast<LPCWSTR>("Windows API");

/* Global flag for our message loop */
bool running = true;

/* Handle to the window */
HWND hWnd = nullptr;

/* A windows callback procedure. */
LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) {
	case WM_CLOSE:
		DestroyWindow(hWnd);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		running = false;
		return 0;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}

/* Entry point of our application */
int WINAPI WinMain(
	HINSTANCE hInstance,		/* A handle to the current instance of the application. */
	HINSTANCE hPrevInstance,	/* A handle to the previous instance of the application. */
	LPSTR lpCmdLine,			/* The command line for the application, excluding the program name. */
	int nCmdShow				/* Controls how the window is to be shown. */
) {
	auto lp_text = reinterpret_cast<LPWSTR>("Hello, Windows API!");
	auto lp_cation = reinterpret_cast<LPWSTR>("Hello");

	WNDCLASSEX WndEx;
	MSG msg;

	WndEx.cbSize = sizeof(WNDCLASSEX);						/* The size, in bytes, of this structure. */
	WndEx.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;		/* The class style(s) */
	WndEx.lpfnWndProc = reinterpret_cast<WNDPROC>(WndProc);	/* A pointer to the window procedure. */
	WndEx.cbClsExtra = 0;									/* The number of extra bytes to allocate following the window-class structure. */
	WndEx.cbWndExtra = 0;									/* The number of extra bytes to allocate following the window instance. */
	WndEx.hIcon = LoadIcon(nullptr, IDI_APPLICATION);		/* A handle to the class icon. */
	WndEx.hCursor = LoadCursor(nullptr, IDC_ARROW);			/* A handle to the class cursor. */
	WndEx.hbrBackground = nullptr;							/* A handle to the class background brush. */
	WndEx.lpszMenuName = nullptr;							/* We're not using a menu here */
	WndEx.lpszClassName = clsName;							/* A pointer to a string that contains the class name */
	WndEx.hInstance = hInstance;							/* A handle to the instance that contains the window procedure for the class. */
	WndEx.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);		/* A handle to a small icon that is associated with the window class */

	if (!RegisterClassEx(&WndEx)) {
		MessageBox(nullptr, reinterpret_cast<LPCWSTR>("Failed to register class"), reinterpret_cast<LPCWSTR>("ERROR"), MB_OK | MB_ICONASTERISK);
		return 0;
	}

	/* Create the window */
	hWnd = CreateWindowEx(
		WS_EX_APPWINDOW |					/* The extended window style */
		WS_EX_WINDOWEDGE,
		clsName,							/* The class name */
		title,								/* The title of the window */
		WS_OVERLAPPEDWINDOW |				/* The style of the window being created */
		WS_CLIPCHILDREN |
		WS_CLIPCHILDREN,
		CW_USEDEFAULT, CW_USEDEFAULT,		/* initial x,y position of the window */
		460, 340,							/* initial x,y size of the window */
		nullptr,							/* A handle to the parent or owner window */
		nullptr,							/* A handle to a menu */
		hInstance,							/* A handle to the instance of the window */
		nullptr);

	if (!hWnd) {
		MessageBox(nullptr, reinterpret_cast<LPCWSTR>("Failed to create the window"), reinterpret_cast<LPCWSTR>("ERROR"), MB_OK | MB_ICONERROR);
		return 0;
	}

	/* The window is initially hidden, we need to show it */
	ShowWindow(hWnd, SW_SHOW);

	/* The main message loop of our program */
	while (running) {

		/* Are there any messages in the message queue? */
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			/* translate and dispatch the message */
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}
