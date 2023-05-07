#pragma once
class Texture
{
public:
	ID3D11Resource* texture;
	ID3D11ShaderResourceView* textureSRV;
	float textureWidth;
	float textureHeight;

public:
	Texture() {}
	~Texture() {}

public:
	bool Init(ID3D11Device* _device, ID3D11DeviceContext* _deviceContext, wstring _filename);
	void Frame();
	void Render();
	void Release();
};

