#include <cstdio>

#include "graphics.h"
#include "app.h"
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
// 642x512

LARGE_INTEGER clock_frequency;
LARGE_INTEGER frame_begin{ 0 };
LARGE_INTEGER frame_end;

LRESULT CALLBACK WindowProc(HWND h_window, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		Graphics::Init(h_window);

		return 0;

	case WM_LBUTTONDOWN:
		App::Run();

		return 0;

	case WM_DESTROY:
		Graphics::DeInit();

		PostQuitMessage(0);

		return 0;
	}

	return DefWindowProc(h_window, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Register the window class
	const wchar_t CLASS_NAME[] = L"0";

	WNDCLASS wc
	{	};
		//.style = CS_HREDRAW | CS_VREDRAW,
		wc.lpfnWndProc = WindowProc,
		wc.hInstance = hInstance,
		wc.hCursor = LoadCursor(NULL, IDC_ARROW),
		//.hbrBackground = GetSysColorBrush(COLOR_MENU),
		wc.lpszClassName = CLASS_NAME,

	RegisterClass(&wc);

	// Adjust window size to client area
	RECT window_rect{ 0, 0, Graphics::width, Graphics::height };

	AdjustWindowRectEx(&window_rect, WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_THICKFRAME), false, WS_EX_DLGMODALFRAME);

	// Create the window
	HWND h_window = CreateWindowEx(
		WS_EX_DLGMODALFRAME, // Optional window styles.
		CLASS_NAME,
		L"Карандаш", // Window title
		WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_THICKFRAME), // Window style

		100, // x
		100, // y
		window_rect.right - window_rect.left, // width
		window_rect.bottom - window_rect.top, // height

		nullptr, // Parent window    
		nullptr, // Menu
		hInstance, // Instance handle
		nullptr // Additional application data
	);

	if (h_window == nullptr)
	{
		return 0;
	}

	ShowWindow(h_window, nCmdShow);

	// Init
	QueryPerformanceFrequency(&clock_frequency);

	App::Init();

	// message loop
	MSG msg;

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}

			//TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			QueryPerformanceCounter(&frame_end);

			uint16_t fps = clock_frequency.QuadPart / (frame_end.QuadPart - frame_begin.QuadPart);

			if (fps < 60)
			{
				QueryPerformanceCounter(&frame_begin);

				char buffer[11]; 

				App::Update();
			}
		}
	}

	return 0;
}