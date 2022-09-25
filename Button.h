#pragma once
#include <d3dx9.h>
#include <dinput.h>
#include <functional>

#include "StateMachine.h"
#include "Label.h"
#include "Line.h"

class Button
{
private:
    bool isHover;
    bool isClick;
    std::function<void(StateMachine*)> onClick;
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
    StateMachine* stateMachine;
    LONG mouseX;
    LONG mouseY;
    DIMOUSESTATE mouseState;
    void SetMouseX(LONG X);
    void SetMouseY(LONG Y);
public:
    Button(std::function<void(StateMachine*)> onClick, LPCSTR buttonText, D3DXVECTOR2 position, D3DXVECTOR2 size,
           D3DCOLOR color, D3DCOLOR textColor, D3DCOLOR hoverColor, D3DCOLOR hoverTextColor, D3DCOLOR clickColor,
           D3DCOLOR clickTextColor, LPDIRECT3DDEVICE9 d3dDevice, StateMachine* stateMachine);
    void CalcRect();
    Label* InitLabel(LPDIRECT3DDEVICE9 d3dDevice);
    Line* InitLine(LPDIRECT3DDEVICE9 d3dDevice);
    void RenderLine();
    void GetInput(LONG mouseX, LONG mouseY, DIMOUSESTATE mouseState);
    void Update();
    void Render(LPD3DXSPRITE spriteBrush);
    void CleanUp();
};
