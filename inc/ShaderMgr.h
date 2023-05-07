#pragma once
#include "Shader.h"

class ShaderMgr
{
	SINGLETON(ShaderMgr);

private:
	ShaderMgr();
	~ShaderMgr();

private:
	map<wstring, Shader*> shaderList;



public:
	bool	Init();
	void	Frame();
	void	Render();
	void	Release();

public:
	Shader* Load(ID3D11Device* _device, ID3D11DeviceContext* _deviceContext, wstring _filename);
};

