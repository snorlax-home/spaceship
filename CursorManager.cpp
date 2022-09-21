#include "CursorManager.h"

CursorManager::CursorManager(int WindowWidth, int WindowHeight, DirectInputManager* directInputManager,
                             IDirect3DDevice9* device)
{
    this->directInputManager = directInputManager;
    this->showCursor = true;
    Init(WindowWidth, WindowHeight, device);
}

void CursorManager::Init(int WindowWidth, int WindowHeight, IDirect3DDevice9* d3dDevice)
{
    D3DXCreateTextureFromFile(d3dDevice, "Assets/cursor.png", &cursorTexture);

    cursorSpriteRect.left = 0;
    cursorSpriteRect.top = 0;
    cursorSpriteRect.right = 64;
    cursorSpriteRect.bottom = 64;

    cursorPosition.y = WindowWidth / 2;
    cursorPosition.x = WindowHeight / 2;
}

void CursorManager::GetInput()
{
    cursorPosition.x += directInputManager->GetMouseState().lX;
    cursorPosition.y += directInputManager->GetMouseState().lY;
    cursorX = cursorPosition.x;
    cursorY = cursorPosition.y;
}

void CursorManager::Render(LPD3DXSPRITE spriteBrush)
{
    D3DCOLOR cursorColor = showCursor ? D3DCOLOR_XRGB(255, 255, 255) : D3DCOLOR_XRGB(0, 0, 0);
    spriteBrush->Draw(cursorTexture, &cursorSpriteRect, NULL,
                      new D3DXVECTOR3(cursorPosition.x, cursorPosition.y, 0),
                      cursorColor);
}

void CursorManager::CleanUp()
{
    cursorTexture->Release();
    cursorTexture = NULL;
    
}

LONG CursorManager::GetCursorX()
{
    return cursorX;
}

LONG CursorManager::GetCursorY()
{
    return cursorY;
}

void CursorManager::SetShowCursor(bool showCursor)
{
    this->showCursor = showCursor;
}
