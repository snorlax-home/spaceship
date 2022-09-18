#include "Label.h"
#include "Utils.cpp"

Label::Label(LPDIRECT3DDEVICE9 d3dDevice, LPCSTR labelText, D3DCOLOR color, D3DXVECTOR2 labelPosition, float width,
             float height, DWORD format)
{
    this->width = width;
    this->height = height;
    this->labelPosition = labelPosition;
    this->labelText = labelText;
    this->color = color;
    this->format = format;
    CalcRect();
    int fontHeight = 20;
    int fontWidth = 0;
    int fontWeight = FW_NORMAL;
    int fontMipLevels = 1;
    bool fontItalic = false;
    DWORD fontCharSet = DEFAULT_CHARSET;
    DWORD fontOutputPrecision = OUT_DEFAULT_PRECIS;
    DWORD fontQuality = DEFAULT_QUALITY;
    DWORD fontPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
    std::string fontFace = "Arial";
    HRESULT hr = D3DXCreateFont(d3dDevice, fontHeight, fontWidth, fontWeight, fontMipLevels, fontItalic,
                                fontCharSet, fontOutputPrecision, fontQuality, fontPitchAndFamily, fontFace.c_str(),
                                &font);
}

void Label::CalcRect()
{
    this->labelRect.left = (long)this->labelPosition.x;
    this->labelRect.top = (long)this->labelPosition.y;
    this->labelRect.right = (long)this->labelPosition.x + this->width;
    this->labelRect.bottom = (long)this->labelPosition.y + this->height;
}

void Label::SetLabelText(LPCSTR labelText)
{
    this->labelText = labelText;
}

void Label::SetColor(D3DCOLOR color)
{
    this->color = color;
}


void Label::Render(LPD3DXSPRITE spriteBrush)
{
    if (font)
    {
        CalcRect();
        font->DrawText(spriteBrush, labelText, lstrlen(labelText), &labelRect, format, color);
    }
}
