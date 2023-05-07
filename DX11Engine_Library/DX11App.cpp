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
        MessageBox(nullptr, L"팩토리 생성 실패", L"오류", 0);
        return false;
    }

    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
    swapChainDesc.BufferCount = 1;                          // 백버퍼 1개. Double Buffering. Screen Tearing. 프론트버퍼, 백퍼버 합쳐서 총 2개 쓴다는 뜻.
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;    // 사용 목적. 화면 출력용으로 쓴다는 뜻.
    swapChainDesc.OutputWindow = _hWnd;    // 출력할 윈도우 설정.
    swapChainDesc.Windowed = true;                          // 창 모드 설정.
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;    // 프론트버퍼와 백버퍼를 바꿀 때, 효과 안 쓴다는 뜻. (요즘엔 빨라서 안 씀).

    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;   // 타입. RGBA를 8비트씩 써라. (0~255 값.) UNORM은 정규화. (0~255 값을 0~1로 바꿈.)
    swapChainDesc.BufferDesc.Width = _WndSize.x;               // 너비.
    swapChainDesc.BufferDesc.Height = _WndSize.y;             // 길이.

    swapChainDesc.SampleDesc.Count = 1;             // 멀티 샘플링 개수 1개. (안 쓴다는 말.) Anti-Alasing.
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
        D3D_DRIVER_TYPE_HARDWARE, // 그래픽 가속기. 요즘엔 이거만 씀. 옛날 꺼 호환한다고 남아 있음.
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
        MessageBox(nullptr, L"장치 생성 실패", L"오류", 0);
        return false;
    }

    ID3D11Texture2D* backbufferTexture;
    result = dx11SwapChain.Get()->GetBuffer(
        NULL,
        __uuidof(ID3D11Texture2D), // 타입 정보 명시. uuidof : 여기에 백퍼버 정보 달라.
        (void**)(&backbufferTexture) // 타입에 상관없이 주소값을 받고 싶을 때 void 포인터.
    );

    if (FAILED(result))
    {
        MessageBox(nullptr, L"백버퍼 정보 얻어오는데 실패", L"오류", 0);
        return false;
    }

    result = dx11Device.Get()->CreateRenderTargetView(
        backbufferTexture,
        nullptr,
        dx11RTView.GetAddressOf()
    );
    if (FAILED(result))
    {
        MessageBox(nullptr, L"렌더타켓뷰 생성 실패", L"오류", 0);
        return false;
    }
    // 임시 버퍼(리소스) 해제.
    backbufferTexture->Release(); // delete 키워드와 하는 일이 같지만, Release로 해야 안전하게 해제 가능.    

    // 렌더 타겟 뷰 할당.(설정)
    dx11Context.Get()->OMSetRenderTargets( // OM : Output Merger 합쳐준다는 의미. 얘는 성공 실패 반환 안 함.
        1, // 화면을 4개로 나눈다면, 4가 입력됨.
        dx11RTView.GetAddressOf(),
        nullptr
    );

    // 뷰포트(화면) - 크기 설정.
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = (float)_WndSize.x;
    viewport.Height = (float)_WndSize.y;

    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;

    // 뷰포트 할당
    dx11Context.Get()->RSSetViewports(1, &viewport); // RS : 레스터라이져

    // 알파블렌드 초기화
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
        MessageBox(nullptr, L"블렌드 스테이트 생성 실패", L"오류", 0);
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
