#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

#include "DirectInputManager.h"

class CursorManager
{
private:
    LONG currentXpos;
    LONG currentYpos;
    LPDIRECT3DTEXTURE9 cursorTexture;
    RECT cursorSpriteRect;
    D3DXVECTOR2 cursorPosition;
    LONG cursorX, cursorY;
    DirectInputManager* directInputManager;
    bool showCursor;
public:
    CursorManager(int WindowWidth, int WindowHeight, DirectInputManager* directInputManager, IDirect3DDevice9* device);
    void Init(int WindowWidth, int WindowHeight, IDirect3DDevice9* d3dDevice);
    void GetInput();
    void Render(LPD3DXSPRITE spriteBrush);
    void CleanUp();
    LONG GetCursorX();
    LONG GetCursorY();
    void SetShowCursor(bool showCursor);
};
