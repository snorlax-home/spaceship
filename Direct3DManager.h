#pragma once
#include <d3d9.h>
#include <d3dx9.h>

#include "WindowsManager.h"
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
class Direct3DManager
{
private:
    IDirect3DDevice9* d3dDevice;
    LPD3DXSPRITE movableBrush;
    LPD3DXSPRITE staticBrush;
    WindowsManager* windowsManager;
public:
    Direct3DManager(WindowsManager* windowsManager, int windowWidth, int windowHeight);
    void Init(int windowWidth, int windowHeight);

    LPD3DXSPRITE GetMovableBrush();
    LPD3DXSPRITE GetStaticBrush();
    IDirect3DDevice9* GetDevice();

    void PreRender();
    void PostRenderGraphics();
    void PostRenderLine();
    void CleanUp();

};
