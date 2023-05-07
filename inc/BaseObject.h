#pragma once
#include "DX11App.h"
#include "Texture.h"
#include "Vector.h"
#include "ShaderMgr.h"

struct SimpleVertex
{
	Vector		p; // 위치
	Vector4D	c;
	Vector2D    t;
};

class BaseObject
{
protected:
	Texture*                      currentTexture; //  현제 렌더링되는 텍스쳐
	list<Texture*>                currentSprite;  //  현재 텍스쳐들의 스프라이트
	map<wstring, list<Texture*>*> spriteList;     //  상태 변화에 따라 변경될 스프라이트 배열

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

public: // 초기화 관련 함수
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

public: // 값 반환 함수
	float GetTextureSizeX();
	float GetTextureSizeY();

	float GetCenterPosX();

	float GetLeftPosX();
	float GetRightPosX();
	float GetTopPosY();
	float GetBottomPosY();

	bool  isEndTexture();

public: // 실시간 계산 함수

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

