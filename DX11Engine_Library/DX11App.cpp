#include "pch.h"
#include "DX11App.h"

DX11App::DX11App()
{
    ZeroMemory(dx11Device.GetAddressOf(),    sizeof(dx11Device.Get()));
    ZeroMemory(dx11Context.GetAddressOf(),   sizeof(dx11Context.Get()));
    ZeroMemory(dxgiFactory.GetAddressOf(),   sizeof(dxgiFactory.Get()));
    ZeroMemory(dx11SwapChain.GetAddressOf(), sizeof(dx11SwapChain.Get()));
    ZeroMemory(dx11RTView.GetAddressOf(),    sizeof(dx11RTView.Get()));
}


DX11App::~DX11App()
{
}

bool DX11App::Init(POINT _WndSize, HWND _hWnd)
{
    HRESULT result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)dxgiFactory.GetAddressOf());
    if (FAILED(result))
    {
        MessageBox(nullptr, L"���丮 ���� ����", L"����", 0);
        return false;
    }

    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
    swapChainDesc.BufferCount = 1;                          // ����� 1��. Double Buffering. Screen Tearing. ����Ʈ����, ���۹� ���ļ� �� 2�� ���ٴ� ��.
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;    // ��� ����. ȭ�� ��¿����� ���ٴ� ��.
    swapChainDesc.OutputWindow = _hWnd;    // ����� ������ ����.
    swapChainDesc.Windowed = true;                          // â ��� ����.
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;    // ����Ʈ���ۿ� ����۸� �ٲ� ��, ȿ�� �� ���ٴ� ��. (���� ���� �� ��).

    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;   // Ÿ��. RGBA�� 8��Ʈ�� ���. (0~255 ��.) UNORM�� ����ȭ. (0~255 ���� 0~1�� �ٲ�.)
    swapChainDesc.BufferDesc.Width = _WndSize.x;               // �ʺ�.
    swapChainDesc.BufferDesc.Height = _WndSize.y;             // ����.

    swapChainDesc.SampleDesc.Count = 1;             // ��Ƽ ���ø� ���� 1��. (�� ���ٴ� ��.) Anti-Alasing.
    swapChainDesc.SampleDesc.Quality = 0;           // Count - 1.

    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    D3D_FEATURE_LEVEL pFeatureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
    };

    result = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE, // �׷��� ���ӱ�. ���� �̰Ÿ� ��. ���� �� ȣȯ�Ѵٰ� ���� ����.
        nullptr,
        D3D11_CREATE_DEVICE_BGRA_SUPPORT,
        pFeatureLevels,
        1,
        D3D11_SDK_VERSION,
        &swapChainDesc,
        dx11SwapChain.GetAddressOf(),
        dx11Device.GetAddressOf(),
        NULL,
        dx11Context.GetAddressOf()
    );
    if (FAILED(result))
    {
        MessageBox(nullptr, L"��ġ ���� ����", L"����", 0);
        return false;
    }

    ID3D11Texture2D* backbufferTexture;
    result = dx11SwapChain.Get()->GetBuffer(
        NULL,
        __uuidof(ID3D11Texture2D), // Ÿ�� ���� ���. uuidof : ���⿡ ���۹� ���� �޶�.
        (void**)(&backbufferTexture) // Ÿ�Կ� ������� �ּҰ��� �ް� ���� �� void ������.
    );

    if (FAILED(result))
    {
        MessageBox(nullptr, L"����� ���� �����µ� ����", L"����", 0);
        return false;
    }

    result = dx11Device.Get()->CreateRenderTargetView(
        backbufferTexture,
        nullptr,
        dx11RTView.GetAddressOf()
    );
    if (FAILED(result))
    {
        MessageBox(nullptr, L"����Ÿ�Ϻ� ���� ����", L"����", 0);
        return false;
    }
    // �ӽ� ����(���ҽ�) ����.
    backbufferTexture->Release(); // delete Ű����� �ϴ� ���� ������, Release�� �ؾ� �����ϰ� ���� ����.    

    // ���� Ÿ�� �� �Ҵ�.(����)
    dx11Context.Get()->OMSetRenderTargets( // OM : Output Merger �����شٴ� �ǹ�. ��� ���� ���� ��ȯ �� ��.
        1, // ȭ���� 4���� �����ٸ�, 4�� �Էµ�.
        dx11RTView.GetAddressOf(),
        nullptr
    );

    // ����Ʈ(ȭ��) - ũ�� ����.
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = (float)_WndSize.x;
    viewport.Height = (float)_WndSize.y;

    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;

    // ����Ʈ �Ҵ�
    dx11Context.Get()->RSSetViewports(1, &viewport); // RS : �����Ͷ�����

    // ���ĺ��� �ʱ�ȭ
    D3D11_BLEND_DESC blendDesc;
    ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));

    blendDesc.RenderTarget[0].BlendEnable = TRUE;

    blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

    blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

    blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    result = dx11Device.Get()->CreateBlendState(&blendDesc, &AlphaBlend);
    if (FAILED(result))
    {
        MessageBox(nullptr, L"���� ������Ʈ ���� ����", L"����", 0);
        return false;
    }

    return true;
}

void DX11App::Frame()
{
}

void DX11App::Clear()
{
    float backgroundColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    dx11Context.Get()->ClearRenderTargetView(dx11RTView.Get(), backgroundColor);
}

void DX11App::Render()
{
    dx11SwapChain.Get()->Present(1, 0);
}

void DX11App::Release()
{
}
