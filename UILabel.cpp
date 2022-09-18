#include "UIObject.h"
#include "UILabel.h"
#include <d3dx9.h>
#include <iostream>
#include <string>
#include "Utils.cpp"

UILabel::UILabel(LPCSTR displayText, LPDIRECT3DDEVICE9 d3dDevice, D3DXVECTOR2 initialPosition, int width, int height, int zIndex) : UIObject()
{
	this->displayText = displayText;
	SetD3DDevice(d3dDevice);
	SetRelativePosition(initialPosition);
	SetWidth(width);
	SetHeight(height);
	SetZIndex(zIndex);
	RECT tempCollisionRect;
	tempCollisionRect.left = initialPosition.x;
	tempCollisionRect.top = initialPosition.y;
	tempCollisionRect.right = initialPosition.x + width;
	tempCollisionRect.bottom = initialPosition.y + height;
	SetCollisionRect(tempCollisionRect);
}

//void PrintLines(std::string message) {
//		std::cout << message << std::endl;
//}

void UILabel::InitUI() {
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
	HRESULT hr = D3DXCreateFont(GetD3DDevice(), fontHeight, fontWidth, fontWeight, fontMipLevels, fontItalic, fontCharSet, fontOutputPrecision, fontQuality, fontPitchAndFamily, fontFace.c_str(), &font);
	switch (hr)
	{
	case S_OK:
		PrintLine("Ok");
		break;
	case D3DERR_INVALIDCALL:
		PrintLine("Invalid Call");
		break;
	case D3DXERR_INVALIDDATA:
		PrintLine("Invalid Data");
		break;
	case E_OUTOFMEMORY:
		PrintLine("Out of memory");
		break;
	}
}

void UILabel::Update(DIMOUSESTATE mouseState)
{
	this->mouseState = mouseState;
}

void UILabel::Render()
{
	if (font)
		font->DrawText(NULL, displayText, -1, &collisionRect, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
	else {
		std::cout << "Font is not init" << std::endl;
	}
}


void UILabel::CleanUp() {
	if(font!=nullptr)
		font->Release();
	font = NULL;
}

LPCSTR UILabel::GetText() {
	return this->displayText;
}

void UILabel::SetText(LPCSTR displayText) {
	this->displayText = displayText;
}

LPD3DXFONT UILabel::GetFont()
{
	return this->font;
}

void UILabel::SetFont(LPD3DXFONT font)
{
	this->font = font;
}

