#include "pch.h"
#include "ShaderMgr.h"

ShaderMgr::ShaderMgr()
{
}

ShaderMgr::~ShaderMgr()
{
}

bool ShaderMgr::Init()
{
	return true;
}

void ShaderMgr::Frame()
{
}

void ShaderMgr::Render()
{
}

void ShaderMgr::Release()
{
}

Shader* ShaderMgr::Load(ID3D11Device* _device, ID3D11DeviceContext* _deviceContext ,wstring _filename)
{
	// 중복 체크
	auto iter = shaderList.find(_filename);
	if (iter != shaderList.end())
	{
		return iter->second;
	}

	Shader* newShader = new Shader;
	if (newShader)
	{
		if (newShader->Init(_device, _deviceContext, _filename))
		{
			shaderList.insert(make_pair(_filename, newShader));
		}
	}


	return newShader;
}
