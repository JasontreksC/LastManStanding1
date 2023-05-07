#include "pch.h"
#include "WriteMgr.h"

bool WriteMgr::Init()
{
	HRESULT hr;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2dFactory);

	if (FAILED(hr))
	{
		MessageBox(nullptr, L"2d 팩토리 생성 실패", L"오류", 0);
		return false;
	}

	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		(IUnknown**)&dwriteFactory);

	if (FAILED(hr))
	{
		MessageBox(nullptr, L"dwrite 팩토리 생성 실패", L"오류", 0);
		return false;
	}


	return true;
}

bool WriteMgr::Frame()
{
	return true;
}

bool WriteMgr::Render(vector<Text*> _textList)
{
	for (auto text : _textList)
		Draw(*text);
	return true;
}

bool WriteMgr::Release()
{
	if (dwriteFactory) dwriteFactory->Release();
	if (d2dRT) d2dRT->Release();
	if (d2dFactory) d2dFactory->Release();
	return true;
}

bool WriteMgr::Set(IDXGISurface1* dxgiSurface)
{
	// 중요 : 디바이스 생성 플래그 지정해야 한다. 
	// UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
	// 3d -> 2D 연동
	D2D1_RENDER_TARGET_PROPERTIES props;
	ZeroMemory(&props, sizeof(props));
	props.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
	props.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED);
	props.dpiX = 96;
	props.dpiY = 96;
	props.usage = D2D1_RENDER_TARGET_USAGE_NONE;
	props.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;

	HRESULT hr = d2dFactory->CreateDxgiSurfaceRenderTarget(
		dxgiSurface,
		&props,
		&d2dRT);

	if (FAILED(hr))
	{
		MessageBox(nullptr, L"렌더타겟 연동 실패", L"오류", 0);
		return false;
	}

	return true;
}

bool WriteMgr::Draw(const Text& _Text)
{
	d2dRT->BeginDraw();

	D2D1_RECT_F rt = { _Text.textPos.x, _Text.textPos.y, 1280, 800};

	//m_pTextColor->SetTransform()
	d2dRT->DrawText(_Text.text.c_str(), _Text.text.size(),
		_Text.textFormat, rt, _Text.textColor);

	d2dRT->EndDraw();
	return true;
}

bool Text::Init(wstring _fontStyle, int _fontSize, POINT _textPos, wstring _text, D2D1_COLOR_F _color)
{
	HRESULT hr = WriteMgr::GetInst()->GetDwriteFactory()->CreateTextFormat(
		_fontStyle.c_str(),//L"Gabriola", //L"고딕",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		_fontSize,
		L"en-us",//, // L"ko-kr",//
		&textFormat);
		
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"텍스트 포맷 생성 실패", L"오류", 0);
		return false;
	}

	hr = WriteMgr::GetInst()->d2dRT->CreateSolidColorBrush({ 0,0,0,1 }, &textColor);

	if (FAILED(hr))
	{
		MessageBox(nullptr, L"브러쉬 생성 실패", L"오류", 0);
		return false;
	}
	textColor->SetColor(_color);
	textColor->SetOpacity(1.0f);

	textPos = _textPos;
	text = _text;

	return true;
}

void Text::Release()
{
	if (textColor) textColor->Release();
}
