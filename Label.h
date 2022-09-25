#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <string>

class Label
{
protected:
    LPD3DXFONT font;
    std::string labelText;
    D3DCOLOR color;
    DWORD format;
    RECT labelRect;
    D3DXVECTOR2 labelPosition;
    float width;
    float height;
public:
    Label(LPDIRECT3DDEVICE9 d3dDevice, std::string labelText, D3DCOLOR color, D3DXVECTOR2 labelPosition, float width, float height, DWORD format);
    void CalcRect();
    void SetLabelText(std::string labelText);
    void SetColor(D3DCOLOR color);
    void Render(LPD3DXSPRITE spriteBrush);
};
