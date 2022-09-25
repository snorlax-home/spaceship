#include "Direct3DManager.h"
#include <iostream>

void HRMessage(HRESULT hr, const char* currentProcess)
{
    if (FAILED(hr))
    {
        std::cout << "Failed : " << currentProcess << std::endl;
    }
    else
    {
        std::cout << "Success : " << currentProcess << std::endl;
    }
}

Direct3DManager::Direct3DManager(WindowsManager* windowsManager, int windowWidth, int windowHeight)
{
    this->windowsManager = windowsManager;
    Init(windowWidth, windowHeight);
}

void Direct3DManager::Init(int windowWidth, int windowHeight)
{
    HRESULT hr;
    IDirect3D9* direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);

    D3DPRESENT_PARAMETERS d3dPP;
    ZeroMemory(&d3dPP, sizeof(d3dPP));

    d3dPP.Windowed = true;
    d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dPP.BackBufferCount = 1;
    d3dPP.MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;
    d3dPP.BackBufferWidth = windowWidth;
    d3dPP.BackBufferHeight = windowHeight;
    d3dPP.hDeviceWindow = windowsManager->GetHandle();

    hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, windowsManager->GetHandle(),
                                 D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                 &d3dPP, &d3dDevice);
    HRMessage(hr, "Create Direct3D9 device.");

    movableBrush = nullptr;
    staticBrush = nullptr;
    hr = D3DXCreateSprite(d3dDevice, &movableBrush);
    HRMessage(hr, "Create graphics brush.");
    hr = D3DXCreateSprite(d3dDevice, &staticBrush);
    HRMessage(hr, "Create text brush.");
}

void Direct3DManager::PreRender()
{
    d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    d3dDevice->BeginScene();
    movableBrush->Begin(D3DXSPRITE_ALPHABLEND);
    staticBrush->Begin(D3DXSPRITE_ALPHABLEND);
    
}

void Direct3DManager::PostRenderGraphics()
{
    movableBrush->End();
    staticBrush->End();
}

void Direct3DManager::PostRenderLine()
{
    d3dDevice->EndScene();
    d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void Direct3DManager::CleanUp()
{
    movableBrush->Release();
    movableBrush = NULL;

    staticBrush->Release();
    staticBrush = NULL;

    d3dDevice->Release();
    d3dDevice = NULL;
}

LPD3DXSPRITE Direct3DManager::GetMovableBrush()
{
    return movableBrush;
}

LPD3DXSPRITE Direct3DManager::GetStaticBrush()
{
    return staticBrush;
}


IDirect3DDevice9* Direct3DManager::GetDevice()
{
    return d3dDevice;
}
