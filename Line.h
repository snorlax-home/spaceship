#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

class Line
{
protected:
    LPD3DXLINE line;
    std::vector<D3DXVECTOR2> vertices;
    int numVertices;
    D3DCOLOR color;
public:
    Line(LPDIRECT3DDEVICE9 d3dDevice, int numVertices, std::vector<D3DXVECTOR2> vertices, D3DCOLOR color);
    ~Line();
    void SetColor(D3DCOLOR color);
    void Render();
    void CleanUp();
};
