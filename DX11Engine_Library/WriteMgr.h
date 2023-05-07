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
	virtual bool		Init(); // �ʱ�ȭ
	virtual bool		Frame();// �ǽð� ���
	virtual bool		Render(vector<Text*> _textList);// �ǽð� ������
	virtual bool		Release();// �Ҹ� �� ����
public:
	bool		Set(IDXGISurface1* dxgiSurface); // ����
	bool		Draw(const Text& _Text);
	IDWriteFactory* GetDwriteFactory() { return dwriteFactory; }
};


