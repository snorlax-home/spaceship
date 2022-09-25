#include "Line.h"
#include "Utils.cpp"

Line::Line(LPDIRECT3DDEVICE9 d3dDevice, int numVertices, std::vector<D3DXVECTOR2> vertices, D3DCOLOR color)
{
    this->line = nullptr;
    this->vertices = vertices;
    D3DXCreateLine(d3dDevice, &this->line);
    this->numVertices = numVertices;
    this->color = color;
}

Line::~Line()
{

}

void Line::SetColor(D3DCOLOR color)
{
    this->color = color;
}

void Line::Render()
{
    line->Begin();
    line->Draw(vertices.data(), vertices.size(), this->color);
    line->End();
}

void Line::CleanUp()
{
    vertices.clear();
}
