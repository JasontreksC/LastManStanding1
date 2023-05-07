#include "pch.h"
#include "Shader.h"

Shader::Shader()
{
}

Shader::~Shader()
{
}

bool Shader::Init(ID3D11Device* _device, ID3D11DeviceContext* _deviceContext, wstring filename)
{
	// VS CompileE
	HRESULT result = D3DCompileFromFile(
		filename.c_str(),
		0, 0, "VS", "vs_5_0", 0, 0,
		&vsCode, 0);
	if (FAILED(result))
	{
		MessageBox(nullptr, L"VS 컴파일 실패", L"오류", 0);
		return false;
	}

	// VS Create
	result = _device->CreateVertexShader(
		vsCode->GetBufferPointer(),
		vsCode->GetBufferSize(),
		NULL,
		&vertexShader
	);
	if (FAILED(result))
	{
		MessageBox(nullptr, L"VS 생성 실패", L"오류", 0);
		return false;
	}

	// PS Compile
	result = D3DCompileFromFile(
		filename.c_str(),
		0, 0, "PS", "ps_5_0", 0, 0,
		&psCode, nullptr);
	if (FAILED(result))
	{
		MessageBox(nullptr, L"PS 컴파일 실패", L"오류", 0);
		return false;
	}
	
	// PS Create
	result = _device->CreatePixelShader(
		psCode->GetBufferPointer(),
		psCode->GetBufferSize(),
		NULL,
		&pixelShader
	);
	if (FAILED(result))
	{
		MessageBox(nullptr, L"PS 생성 실패", L"오류", 0);
		return false;
	}

	return true;
}

bool Shader::Frame()
{
	return false;
}

bool Shader::Render()
{
	return false;
}

bool Shader::Release()
{
	return false;
}
