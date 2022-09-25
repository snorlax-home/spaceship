#pragma once
#include <d3d9.h>
#include <d3dx9.h>

#include "WindowsManager.h"
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
class DirectXManager
{
private:
    IDirect3DDevice9* d3dDevice;
    LPD3DXSPRITE graphicsBrush;
    LPD3DXSPRITE textBrush;
    WindowsManager* windowsManager;
public:
    DirectXManager(WindowsManager* windowsManager, int windowWidth, int windowHeight);
    void Init(int windowWidth, int windowHeight);
    void PreRender();
    void PostRenderGraphics();
    void PostRenderLine();
    void CleanUp();
    LPD3DXSPRITE GetGraphicsBrush();
    LPD3DXSPRITE GetTextBrush();
    IDirect3DDevice9* GetDevice();
};
