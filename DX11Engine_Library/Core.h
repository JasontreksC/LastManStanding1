#pragma once
#include "Window.h"
#include "DX11App.h"
#include "WriteMgr.h"
#include "TimeMgr.h"
#include "SoundMgr.h"

class Core
{
protected:
	Window window;

public:
	virtual bool Init(HINSTANCE _hInstance, wstring _title, int _width, int _height);
	virtual void Frame();
	virtual void Render();
	virtual void Release();
};

