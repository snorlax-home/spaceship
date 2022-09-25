#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

/**
 * \brief UI Line component
 *
 * This UI Line is a simple line that can be drawn on the screen.
 */
class Line
{
private:
    LPD3DXLINE line;
    std::vector<D3DXVECTOR2> vertices;
    int numVertices;
    D3DCOLOR color;
public:
    /**
     * \brief Line Default Constructor
     * \param d3dDevice D3D Device for Creating line interface
     * \param numVertices Number of vertices of the line 
     * \param vertices Vector of vertices of the line
     * \param color Color of the line
     */
    Line(LPDIRECT3DDEVICE9 d3dDevice, int numVertices, std::vector<D3DXVECTOR2> vertices, D3DCOLOR color);
    ~Line();
    /**
     * \brief Color Setter
     * \param color Set the property of color
     */
    void SetColor(D3DCOLOR color);
    /**
     * \brief Render the line
     */
    void Render();
    /**
     * \brief Clean Up the line
     * Clear the vertices vector
     */
    void CleanUp();
};
