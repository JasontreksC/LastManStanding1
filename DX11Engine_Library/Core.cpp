#include "pch.h"
#include "Core.h"

bool Core::Init(HINSTANCE _hInstance, wstring _title, int _width, int _height)
{
    // 윈도우, DX 초기화
    if (window.init(_hInstance, _title, _width, _height) == false)
        return false;

    if (DXAPP_INSTANCE->Init(window.GetWndSize(), window.GetWndHandle()) == false)
        return false;

    return true;
}

void Core::Frame()
{
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) == TRUE)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
        }
    }
}

void Core::Render()
{
    DXAPP_INSTANCE->Clear();


    DXAPP_INSTANCE->Render();
}

void Core::Release()
{
}
