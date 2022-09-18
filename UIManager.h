#pragma once

#include <d3d9.h>
#include <d3dx9.h>

enum TextAlign { left, centered, right };

struct vertex
{
    FLOAT x, y, z, rhw;
    DWORD color;
};

class UIManager
{
    ID3DXFont* pFont;

    void Line(D3DXVECTOR2 startPoint, D3DXVECTOR2 endPoint, float width, float height, DWORD color);
    

    void Init();
};
