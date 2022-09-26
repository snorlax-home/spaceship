#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <string>

/**
 * \brief UI Component Label
 *
 * This UI Label si use for display a text
 */
class Label
{
private:
    LPD3DXFONT font;
    std::string labelText;
    D3DCOLOR color;
    DWORD format;
    RECT labelRect;
    D3DXVECTOR2 labelPosition;
    float width;
    float height;
public:
    /**
     * \brief Label Default Constructor
     *
     * \param d3dDevice D3D Device to create font 
     * \param labelText Text to be display
     * \param color Color of the label text
     * \param labelPosition Position of label
     * \param width Width of the label
     * \param height Height of the label
     * \param format Format of the label
     */
    Label(LPDIRECT3DDEVICE9 d3dDevice, std::string labelText, D3DCOLOR color, D3DXVECTOR2 labelPosition, float width,
          float height, DWORD format);
    /**
     * \brief Calculate Position Rectangle
     *
     * Function to recalculate the position rectangle of the button
     */
    void CalcRect();
    /**
     * \brief Set the label text 
     * \param labelText String to be display
     */
    void SetLabelText(std::string labelText);
    /**
     * \brief Set position of label
     * \param labelPosition Position of label
     */
    void SetLabelPosition(D3DXVECTOR2 labelPosition);
    /**
     * \brief Set color of label text
     * \param color Color of the label
     */
    void SetColor(D3DCOLOR color);
    /**
     * \brief Get position of label
     * \return Vector of position of label
     */
    D3DXVECTOR2 GetLabelPosition();
    /**
     * \brief Render the label
     * \param spriteBrush Sprite brush to draw out the label
     */
    void Render(LPD3DXSPRITE spriteBrush);
    /**
     * \brief Clean Up
     */
    void CleanUp();
};
