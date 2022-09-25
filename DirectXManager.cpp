#include "DirectXManager.h"
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

DirectXManager::DirectXManager(WindowsManager* windowsManager, int windowWidth, int windowHeight)
{
    this->windowsManager = windowsManager;
    Init(windowWidth, windowHeight);
}

void DirectXManager::Init(int windowWidth, int windowHeight)
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

    graphicsBrush = nullptr;
    textBrush = nullptr;
    hr = D3DXCreateSprite(d3dDevice, &graphicsBrush);
    HRMessage(hr, "Create graphics brush.");
    hr = D3DXCreateSprite(d3dDevice, &textBrush);
    HRMessage(hr, "Create text brush.");
}

void DirectXManager::PreRender()
{
    d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    d3dDevice->BeginScene();
    graphicsBrush->Begin(D3DXSPRITE_ALPHABLEND);
    textBrush->Begin(D3DXSPRITE_ALPHABLEND);
    
}

void DirectXManager::PostRenderGraphics()
{
    graphicsBrush->End();
    textBrush->End();
}

void DirectXManager::PostRenderLine()
{
    d3dDevice->EndScene();
    d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void DirectXManager::CleanUp()
{
    graphicsBrush->Release();
    graphicsBrush = NULL;

    textBrush->Release();
    textBrush = NULL;

    d3dDevice->Release();
    d3dDevice = NULL;
}

LPD3DXSPRITE DirectXManager::GetGraphicsBrush()
{
    return graphicsBrush;
}

LPD3DXSPRITE DirectXManager::GetTextBrush()
{
    return textBrush;
}


IDirect3DDevice9* DirectXManager::GetDevice()
{
    return d3dDevice;
}
