#pragma once
struct Text
{
	IDWriteTextFormat* textFormat;
	ID2D1SolidColorBrush* textColor;
	wstring		text;
	POINT textPos;
	bool Init(wstring _fontStyle, int _fontSize, POINT _textPos, wstring _text, D2D1_COLOR_F _color);
	void Release();
};

class WriteMgr
{
	SINGLETON(WriteMgr)
private:
	WriteMgr() {}
	~WriteMgr() {}

public:
	ID2D1Factory* d2dFactory;
	IDWriteFactory* dwriteFactory;
	ID2D1RenderTarget* d2dRT;
public:
	virtual bool		Init(); // 초기화
	virtual bool		Frame();// 실시간 계산
	virtual bool		Render(vector<Text*> _textList);// 실시간 랜더링
	virtual bool		Release();// 소멸 및 삭제
public:
	bool		Set(IDXGISurface1* dxgiSurface); // 연동
	bool		Draw(const Text& _Text);
	IDWriteFactory* GetDwriteFactory() { return dwriteFactory; }
};


