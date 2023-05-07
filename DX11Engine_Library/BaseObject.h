#pragma once
#include "DX11App.h"
#include "Texture.h"
#include "Vector.h"
#include "ShaderMgr.h"

struct SimpleVertex
{
	Vector		p; // ��ġ
	Vector4D	c;
	Vector2D    t;
};

class BaseObject
{
protected:
	Texture*                      currentTexture; //  ���� �������Ǵ� �ؽ���
	list<Texture*>                currentSprite;  //  ���� �ؽ��ĵ��� ��������Ʈ
	map<wstring, list<Texture*>*> spriteList;     //  ���� ��ȭ�� ���� ����� ��������Ʈ �迭

protected:
	vector<SimpleVertex> vertexList;
	ID3D11Buffer* vertexBuffer;
	ID3D11InputLayout* inputLayout;
	Shader* shader;

public:
	float ObjectPosX = 0;
	float ObjectPosY = 0;
	float frame = 0;
	int spriteIndex = 0;

public: // �ʱ�ȭ ���� �Լ�
	virtual bool Init();//not used//

	bool Create(wstring shaderName);
	bool CreateVertexBuffer(wstring shaderName);
	bool CreateShader(wstring _filename);
	bool CreateVertexLayout();
	void MakeSprite(wstring _spriteName, wstring _fileName, int _sheets, wstring _fileType);

	void SetObjScale_ByTextureSize();
	void SetObjScale_ByManual(float _scalar);
	void SetObjSclae_Dynaic(HWND _hWnd);

	void SetPos_InWorld(float _x, float _y);
	void SetPos_InNDC(float _x, float _y);

public: // �� ��ȯ �Լ�
	float GetTextureSizeX();
	float GetTextureSizeY();

	float GetCenterPosX();

	float GetLeftPosX();
	float GetRightPosX();
	float GetTopPosY();
	float GetBottomPosY();

	bool  isEndTexture();

public: // �ǽð� ��� �Լ�

	virtual void SetSprite(wstring _spriteName);
	virtual int  Animate(float _speed);
	virtual void Frame();
	virtual bool Move(float _Xspeed, float _Yspeed);
	virtual void Stay();
	virtual void Reverse_R();
	virtual void Reverse_L();
	virtual void Render();
	virtual void Release();
		
};

