#include "pch.h"
#include "Texture.h"

bool Texture::Init(ID3D11Device* _device, ID3D11DeviceContext* _deviceContext, wstring _filename)
{
    HRESULT result = DirectX::CreateWICTextureFromFile(
        _device,
        _deviceContext,
        _filename.c_str(),
        &texture,
        &textureSRV);
    
    if (FAILED(result))
    {
        MessageBox(nullptr, L"텍스쳐 로드 실패", L"오류", 0);
        return false;
    }

    // 텍스쳐 너비, 높이 가져오기
    ID3D11Texture2D* pTextureInterface = 0;
    texture->QueryInterface<ID3D11Texture2D>(&pTextureInterface);
    D3D11_TEXTURE2D_DESC desc;
    pTextureInterface->GetDesc(&desc);
    textureWidth = (float)desc.Width;
    textureHeight = (float)desc.Height;

    pTextureInterface->Release();

    return true;
}
