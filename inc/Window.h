#pragma once
class Window
{
private:
	HINSTANCE hInstance;
	HWND      hWnd;
	wstring   title;
	POINT     WndSize;
	HICON     hIcon;
public:
	HWND GetWndHandle() { return hWnd; }
	POINT GetWndSize() { return WndSize; }

public:
	bool init(HINSTANCE _hInstance, wstring _title, int _width, int _height);
	void Frame();
	void Render();
	void Release();
};
