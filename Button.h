#pragma once
#include <d3dx9.h>
#include <dinput.h>
#include <functional>

#include "GameLevelManager.h"
#include "Label.h"
#include "Line.h"

class Button
{
protected:
    bool isHover;
    bool isClick;
    std::function<void(GameLevelManager*)> onClick;
    LPCSTR buttonText;
    D3DXVECTOR2 position;
    D3DXVECTOR2 size;
    RECT rect;
    D3DCOLOR color;
    D3DCOLOR textColor;
    D3DCOLOR hoverColor;
    D3DCOLOR hoverTextColor;
    D3DCOLOR clickColor;
    D3DCOLOR clickTextColor;
    Label* label;
    Line* line;
    GameLevelManager* gameLevelManager;
public:
    Button(std::function<void(GameLevelManager*)> onClick, LPCSTR buttonText, D3DXVECTOR2 position, D3DXVECTOR2 size,
           D3DCOLOR color, D3DCOLOR textColor, LPDIRECT3DDEVICE9 d3dDevice, GameLevelManager* gameLevelManager);
    Button(std::function<void(GameLevelManager*)> onClick, LPCSTR buttonText, D3DXVECTOR2 position, D3DXVECTOR2 size,
           D3DCOLOR color, D3DCOLOR textColor, D3DCOLOR hoverColor, D3DCOLOR hoverTextColor, D3DCOLOR clickColor,
           D3DCOLOR clickTextColor, LPDIRECT3DDEVICE9 d3dDevice, GameLevelManager* gameLevelManager);
    void CalcRect();
    Label* InitLabel(LPDIRECT3DDEVICE9 d3dDevice);
    Line* InitLine(LPDIRECT3DDEVICE9 d3dDevice);
    void RenderLine();
    void Update(LONG mouseX, LONG mouseY, DIMOUSESTATE mouseState);
    void Render(LPD3DXSPRITE spriteBrush);
};
