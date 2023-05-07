#pragma once
class Shader
{
public:
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader*  pixelShader;

public:
	ID3DBlob* vsCode = nullptr;
	ID3DBlob* psCode = nullptr;

public:
	Shader();
	~Shader();

public:
	bool	Init(ID3D11Device* _device, ID3D11DeviceContext* _deviceContext, wstring filename);
	bool	Frame();
	bool	Render();
	bool	Release();
};