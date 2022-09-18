#include "UIObject.h"
#include <iostream>


UIObject::UIObject()
{
}

UIObject::~UIObject()
{
}

void UIObject::SetD3DDevice(LPDIRECT3DDEVICE9 d3dDevice)
{
	this->d3dDevice = d3dDevice;
}

void UIObject::SetRelativePosition(D3DXVECTOR2 relativePosition)
{
	this->relativePosition = relativePosition;
}

void UIObject::SetWidth(int width)
{
	this->width = width;
}

void UIObject::SetHeight(int height)
{
	this->height = height;
}

void UIObject::SetZIndex(int zIndex)
{
	this->zIndex = zIndex;
}

void UIObject::SetCollisionRect(RECT collisionRect)
{
	this->collisionRect = collisionRect;
}

LPDIRECT3DDEVICE9 UIObject::GetD3DDevice()
{
	return this->d3dDevice;
}

D3DXVECTOR2 UIObject::GetRelativePosition()
{
	return this->relativePosition;
}

int UIObject::GetWidth()
{
	return this->width;
}

int UIObject::GetHeight()
{
	return this->height;
}

int UIObject::GetZIndex()
{
	return this->zIndex;
}

RECT UIObject::GetCollisionRect()
{
	return this->collisionRect;
}

//void UIObject::InitUI()
//{
//}
//
//void UIObject::Update(DIMOUSESTATE mouseState)
//{
//	this->mouseState = mouseState;
//}
//
//void UIObject::Render()
//{
//	std::cout << "Render" << std::endl;
//}
//
//void UIObject::CleanUp()
//{
//	
//}

void UIObject::UpdateUIPosition(D3DXVECTOR2 newPosition)
{
	this->relativePosition = newPosition;
	this->collisionRect.left = this->relativePosition.x;
	this->collisionRect.right = this->collisionRect.left + this->width;
	this->collisionRect.top = this->relativePosition.y;
	this->collisionRect.bottom = this->collisionRect.top + this->height;
}

//bool UIObject::operator<(const UIObject& o) const
//{
//	return this->zIndex < o.zIndex;
//}