#include "pch.h"
#include "BaseObject.h"
#include "TimeMgr.h"

bool BaseObject::CreateVertexBuffer(wstring shaderName)
{
    vertexList.resize(6);
    vertexList[0].p = { -1.0f, 1.0f, 0.0f };
    vertexList[1].p = { +1.0f, 1.0f,  0.0f };
    vertexList[2].p = { -1.0f, -1.0f, 0.0f };
    vertexList[3].p = { -1.0f, -1.0f, 0.0f };
    vertexList[4].p = { +1.0f, 1.0f,  0.0f };
    vertexList[5].p = { +1.0f, -1.0f, 0.0f };

    vertexList[0].c = { 1.0f, 0.0f, 0.0f, 0.0f };
    vertexList[1].c = { 1.0f, 0.0f, 0.0f, 0.0f };
    vertexList[2].c = { 1.0f, 0.0f, 0.0f, 0.0f };
    vertexList[3].c = { 1.0f, 0.0f, 0.0f, 0.0f };
    vertexList[4].c = { 1.0f, 0.0f, 0.0f, 0.0f };
    vertexList[5].c = { 1.0f, 0.0f, 0.0f, 0.0f };

    vertexList[0].t = { 0.0f, 0.0f };
    vertexList[1].t = { 1.0f, 0.0f };
    vertexList[2].t = { 0.0f, 1.0f };
    vertexList[3].t = { 0.0f, 1.0f };
    vertexList[4].t = { 1.0f, 0.0f };
    vertexList[5].t = { 1.0f, 1.0f };

    UINT NumVertex = vertexList.size();
    D3D11_BUFFER_DESC       bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(SimpleVertex) * NumVertex; // 바이트 용량
    // GPU 메모리에 할당
    bd.Usage = D3D11_USAGE_DEFAULT; // 버퍼의 할당 장소 내지는 버퍼용도
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA  sd;
    ZeroMemory(&sd, sizeof(sd));

    sd.pSysMem = &vertexList.at(0);
    HRESULT result = DXAPP_INSTANCE->GetDevice()->CreateBuffer(
        &bd, // 버퍼 할당
        &sd, // 초기 할당된 버퍼를 체우는 CPU메모리 주소
        &vertexBuffer);
    if (FAILED(result))
    {
        MessageBox(nullptr, L"VS 버퍼 생성 실패", L"오류", 0);
        return false;
    }

    return true;
}

bool BaseObject::CreateShader(wstring _filename)
{
    shader = ShaderMgr::GetInst()->Load(DXAPP_INSTANCE->GetDevice(), DXAPP_INSTANCE->GetDeviceContext(), _filename);
    if (!shader)
        return false;

    return true;
}

bool BaseObject::CreateVertexLayout()
{
    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,0,D3D11_INPUT_PER_VERTEX_DATA, 0},
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,12,D3D11_INPUT_PER_VERTEX_DATA, 0},
        { "TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT, 0,28,D3D11_INPUT_PER_VERTEX_DATA, 0}
    };
    UINT numElements = sizeof(ied) / sizeof(ied[0]);
    HRESULT result = DXAPP_INSTANCE->GetDevice()->CreateInputLayout(
        ied,
        numElements,
        shader->vsCode->GetBufferPointer(),
        shader->vsCode->GetBufferSize(),
        &inputLayout
    );
    if (FAILED(result))
    {
        MessageBox(nullptr, L"레이아웃 생성 실패", L"오류", 0);
        return false;
    }
    return true;
}

void BaseObject::MakeSprite(wstring _spriteName, wstring _fileName, int _sheets, wstring _fileType)
{
    list<Texture*>* newSprite = new list<Texture*>;

    for (int i = 1; i <= _sheets; ++i)
    {
        Texture* newTexture = new Texture;
        if (newTexture)
        {
            wstring filename = _fileName + to_wstring(i) + _fileType;


            if (newTexture->Init(DXAPP_INSTANCE->GetDevice(), DXAPP_INSTANCE->GetDeviceContext(), filename))
            {
                newSprite->push_back(newTexture);
            }
        }
    }
    spriteList.insert(make_pair(_spriteName.c_str(), newSprite));

    currentSprite = *(spriteList.begin()->second);
    currentTexture = *(currentSprite.begin());
}

bool BaseObject::Create(wstring shaderName)
{
    if (CreateVertexBuffer(shaderName) == false)
        return false;

    if (CreateShader( shaderName) == false)
        return false;

    if (CreateVertexLayout() == false)
        return false;

    return true;
}

bool BaseObject::Init()
{
    return true;
}

void BaseObject::SetObjScale_ByTextureSize()
{
    // 화면상 실제 크기만큼 조정
    float widthRatio = 0;
    float heightRatio = 0;

    widthRatio = currentTexture->textureWidth / 1280.f;
    heightRatio = currentTexture->textureHeight / 800.f;

    for (int i = 0; i < 6; ++i)
    {
        vertexList[i].p.v[0] *= widthRatio;
        vertexList[i].p.v[1] *= heightRatio;
    }
}

void BaseObject::SetObjScale_ByManual(float _scalar)
{
    // 사이즈 직접 조정
    for (int i = 0; i < 6; ++i)
    {
        vertexList[i].p.v[0] *= _scalar;
        vertexList[i].p.v[1] *= _scalar;
    }
}

void BaseObject::SetObjSclae_Dynaic(HWND _hWnd)
{
    // 화면의 크기에 맞는 비율로 동적 조정
    vertexList[0].p = { -1.0f, 1.0f, 0.0f };
    vertexList[1].p = { +1.0f, 1.0f,  0.0f };
    vertexList[2].p = { -1.0f, -1.0f, 0.0f };
    vertexList[3].p = { -1.0f, -1.0f, 0.0f };
    vertexList[4].p = { +1.0f, 1.0f,  0.0f };
    vertexList[5].p = { +1.0f, -1.0f, 0.0f };

    float widthRatio = 0;
    float heightRatio = 0;

    RECT rt;
    GetClientRect(_hWnd, &rt);

    widthRatio = currentTexture->textureWidth / (float)rt.right;
    heightRatio = currentTexture->textureHeight / (float)rt.bottom;

    for (int i = 0; i < 6; ++i)
    {
        vertexList[i].p.v[0] *= widthRatio;
        vertexList[i].p.v[1] *= heightRatio;
    }

    //위치를 다시 잡아준다.
    for (int i = 0; i < 6; ++i)
    {
        vertexList[i].p.v[0] -= ObjectPosX;
    }
    for (int i = 0; i < 6; ++i)
    {
        vertexList[i].p.v[1] -= ObjectPosY;
    }
}

void BaseObject::SetPos_InWorld(float _x, float _y)
{
    float tempX = _x / 1280.0f;
    float tempY = _y / 800.0f;

    for (int i = 0; i < 6; ++i)
    {
        vertexList[i].p.v[0] += tempX;
    }
    for (int i = 0; i < 6; ++i)
    {
        vertexList[i].p.v[1] -= tempY;
    }
}

void BaseObject::SetPos_InNDC(float _x, float _y)
{
    float xTerm = this->vertexList[0].p.v[0] - _x;
    float yTerm = this->vertexList[0].p.v[1] - _y;

    for (int i = 0; i < 6; ++i)
    {
        vertexList[i].p.v[0] -= xTerm;
    }
    for (int i = 0; i < 6; ++i)
    {
        vertexList[i].p.v[1] += yTerm;
    }
}

float BaseObject::GetTextureSizeX()
{
    return currentTexture->textureWidth;
}

float BaseObject::GetTextureSizeY()
{
    return currentTexture->textureHeight;
}

float BaseObject::GetLeftPosX()
{
    return vertexList[0].p.v[0];
}

float BaseObject::GetRightPosX()
{
    return vertexList[1].p.v[0];
}

float BaseObject::GetTopPosY()
{
    return vertexList[0].p.v[1];
}

float BaseObject::GetBottomPosY()
{
    return vertexList[2].p.v[1];
}

bool BaseObject::isEndTexture()
{
    if (currentTexture == currentSprite.back())
        return true;
    return false;
}

void BaseObject::SetSprite(wstring _spriteName)
{
    if (currentSprite != *(spriteList.find(_spriteName.c_str())->second))
    {
        currentSprite = *(spriteList.find(_spriteName.c_str())->second);
        currentTexture = *(currentSprite.begin());
        spriteIndex = 0;
    }
}

void BaseObject::Frame()
{
    DXAPP_INSTANCE->GetDeviceContext()->UpdateSubresource(vertexBuffer, 0, NULL, &vertexList.at(0), 0, 0);
}

int BaseObject::Animate(float _speed)
{
    frame += _speed;
    spriteIndex++;
    if (frame >= 1.0f)
    {
        auto iter = currentSprite.begin();
        while (1)
        {
            if (*iter == currentTexture)
                break;
            ++iter;
        }
        if (++iter != currentSprite.end())
            currentTexture = *iter;
        else 
        {
            currentTexture = *currentSprite.begin();
            spriteIndex = 0;
        }
        frame = 0.0f;
    }
    return spriteIndex;
}

bool BaseObject::Move(float _Xspeed, float _Yspeed)
{
// 가로/세로 이동   
    for (int i = 0; i < 6; ++i)
    {
        vertexList[i].p.v[0] -= _Xspeed * TimeMgr::GetInst()->GetDeltaTime();
    }

    for (int i = 0; i < 6; ++i)
    {
        vertexList[i].p.v[1] -= _Yspeed * TimeMgr::GetInst()->GetDeltaTime();
    }
    ObjectPosX += _Xspeed;
    ObjectPosY += _Yspeed;

    return true;
}

void BaseObject::Stay()
{
    currentTexture = *(currentSprite.begin());
}

void BaseObject::Reverse_R()
{
    vertexList[0].t = {1.0f, 0.0f};
    vertexList[1].t = {0.0f, 0.0f};
    vertexList[2].t = {1.0f, 1.0f};
    vertexList[3].t = {1.0f, 1.0f};
    vertexList[4].t = {0.0f, 0.0f};
    vertexList[5].t = {0.0f, 1.0f};
}

void BaseObject::Reverse_L()
{
    vertexList[0].t = { 0.0f, 0.0f };
    vertexList[1].t = { 1.0f, 0.0f };
    vertexList[2].t = { 0.0f, 1.0f };
    vertexList[3].t = { 0.0f, 1.0f };
    vertexList[4].t = { 1.0f, 0.0f };
    vertexList[5].t = { 1.0f, 1.0f };
}

void BaseObject::Render()
{
    UINT stride = sizeof(SimpleVertex);
    UINT offset = 0;

    // 레지스터리SLOT
    DXAPP_INSTANCE->GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
    DXAPP_INSTANCE->GetDeviceContext()->IASetInputLayout(inputLayout);
    DXAPP_INSTANCE->GetDeviceContext()->VSSetShader(shader->vertexShader, 0, 0);
    DXAPP_INSTANCE->GetDeviceContext()->PSSetShader(shader->pixelShader, 0, 0);
    DXAPP_INSTANCE->GetDeviceContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    
    // 텍스쳐
    DXAPP_INSTANCE->GetDeviceContext()->OMSetBlendState(DXAPP_INSTANCE->GetAlphaBlend(), 0, -1);
    DXAPP_INSTANCE->GetDeviceContext()->PSSetShaderResources(0, 1, &currentTexture->textureSRV);
    DXAPP_INSTANCE->GetDeviceContext()->Draw(vertexList.size(), 0);
}

void BaseObject::Release()
{
}

float BaseObject::GetCenterPosX()
{
    return ((vertexList[1].p.v[0] - vertexList[0].p.v[0]) / 2) + vertexList[0].p.v[0];
}
