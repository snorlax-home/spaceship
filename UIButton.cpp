#include "UIButton.h"

UIButton::UIButton(LPCSTR labelText, LPDIRECT3DDEVICE9 d3dDevice, D3DXVECTOR2 initialPosition, int width, int height, int zIndex, HRESULT(*onClick)()) : UIObject()
{
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
	this->label = new UILabel(labelText, d3dDevice, initialPosition, width, height, zIndex);
}

void UIButton::SetLabel(LPCSTR labelText)
{
	this->label->SetText(labelText);
}

//UILabel UIButton::GetLabel()
//{
//	return *label;
//}

std::string UIButton::GetLabelText()
{
	return label->GetText();
}

void UIButton::InitUI()
{
	HRESULT hr = D3DXCreateLine(GetD3DDevice(), &line);
	hr;
}

void UIButton::Update(DIMOUSESTATE mouseState)
{
	// Setup mouse info
	LONG mouseX = mouseState.lX;
	LONG mouseY = mouseState.lY;
	bool lmbClicked = (mouseState.rgbButtons[0] & 0x80);
	bool rmbClicked = (mouseState.rgbButtons[0] & 0x80);
	RECT mouseRect;
	mouseRect.top = 0 + mouseY;
	mouseRect.bottom = 1 + mouseY;
	mouseRect.left = 0 + mouseX;
	mouseRect.right = 1 + mouseX;

	// Check Collision
	bool isCollide = false;
	if ((mouseRect.left < collisionRect.right) && (mouseRect.right > collisionRect.left) && (mouseRect.bottom < collisionRect.top) && (mouseRect.top > collisionRect.bottom)) {
		isCollide = true;
	}

	if (isCollide && lmbClicked)
	{
		isClicked = true;
	}

	isClicked ? color = D3DCOLOR_XRGB(255, 0, 0) : color = D3DCOLOR_XRGB(255, 255, 255);
	D3DXVECTOR2 lineVertices[] = {
		D3DXVECTOR2(relativePosition.x,relativePosition.y),
		D3DXVECTOR2(relativePosition.x + width,relativePosition.y),
		D3DXVECTOR2(relativePosition.x + width,relativePosition.y + height),
		D3DXVECTOR2(relativePosition.x ,relativePosition.y + height),
		D3DXVECTOR2(relativePosition.x,relativePosition.y)
	};
	this->vertex = lineVertices;
}

void UIButton::Render()
{
	line->Draw(vertex, 4, color);
}

void UIButton::CleanUp()
{
	line->Release();
	line = NULL;
}
