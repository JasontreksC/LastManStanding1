#include "pch.h"
#include "Window.h"

LRESULT CALLBACK WindowProc(
	HWND hwnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
			return 0;
		}
		break;

	case WM_GETMINMAXINFO :
		((LPMINMAXINFO)lParam)->ptMaxTrackSize.x = 1280;
		((LPMINMAXINFO)lParam)->ptMaxTrackSize.y = 800;
		((LPMINMAXINFO)lParam)->ptMinTrackSize.x = 1280;
		((LPMINMAXINFO)lParam)->ptMinTrackSize.y = 800;
		return false;
		break;
	} 
	return DefWindowProc(hwnd, msg, wParam, lParam);
}


bool Window::init(HINSTANCE _hInstance, wstring _title, int _width, int _height)
{
	hInstance = _hInstance;
	title = _title;
	WndSize.x = _width;
	WndSize.y = _height;

	WNDCLASS WindowClass;
	ZeroMemory(&WindowClass, sizeof(WindowClass));

	WindowClass.hInstance = hInstance;
	WindowClass.lpszClassName = (LPCWSTR)&_title;
	WindowClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	WindowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	WindowClass.lpfnWndProc = WindowProc;

	if (RegisterClass(&WindowClass) == false)
	{
		MessageBox(nullptr, L"클래스 등록 실패", L"오류", 0);
		return false;
	}

	RECT rect = { 0, 0, WndSize.x, WndSize.y };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	WndSize.x = rect.right - rect.left;
	WndSize.y = rect.bottom - rect.top;

	hWnd = CreateWindow(
		WindowClass.lpszClassName,
		title.c_str(),
		WS_OVERLAPPEDWINDOW,
		GetSystemMetrics(SM_CXSCREEN) / 2 - WndSize.x / 2,
		GetSystemMetrics(SM_CYSCREEN) / 2 - WndSize.y / 2,
		WndSize.x, WndSize.y,
		NULL, NULL,
		hInstance,
		NULL
	);

	if (hWnd == nullptr)
	{
		MessageBox(nullptr, L"윈도우 생성 실패", L"오류", 0);
		return false;
	}

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	return true;
}
