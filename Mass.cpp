#include "Mass.h"
#include <iostream>

using namespace std;

Mass::Mass()
{
	hp = 0;
	mass = 0;
	consumed = false;
}

Mass::~Mass()
{
	delete this;
}

void Mass::Init(int textureWidth, int textureHeight, int spriteWidth, int spriteHeight, int windowWidth, int windowHeight, float mass, int massHp)
{
	int positionX = rand() % (windowWidth - spriteHeight);
	int positionY = rand() % (windowHeight - spriteHeight);

	GameObject::Init(textureWidth, textureHeight, spriteWidth, spriteHeight, positionX, positionY);
	this->hp = massHp;
	this->mass = mass;
	
	InitDisplayRect();
}

// Setters
void Mass::SetTextureWidth(int spriteWidth)
{
	GameObject::SetTextureWidth(spriteWidth);
}

void Mass::SetTextureHeight(int spriteHeight)
{
	GameObject::SetTextureHeight(spriteHeight);
}

void Mass::SetSpriteWidth(int spriteWidth)
{
	GameObject::SetSpriteWidth(spriteWidth);
}

void Mass::SetSpriteHeight(int spriteHeight)
{
	GameObject::SetSpriteHeight(spriteHeight);
}

void Mass::SetScaling(float scalingX, float scalingY)
{
	GameObject::SetScaling(scalingX, scalingY);
}

void Mass::SetPosition(D3DXVECTOR2 position)
{
	GameObject::SetPosition(position);
}

void Mass::SetPosition(float x, float y)
{
	GameObject::SetPosition(x, y);
}

void Mass::SetPositionX(float x)
{
	GameObject::SetPositionX(x);
}

void Mass::SetPositionY(float y)
{
	GameObject::SetPositionY(y);
}

void Mass::SetMass(float newMass)
{
	this->mass = newMass;
}

void Mass::SetHp(int hp)
{
	this->hp = hp;
}

void Mass::SetConsumed(bool consumed)
{
	this->consumed = consumed;
}

// Getters

int Mass::GetTextureWidth()
{
	return GameObject::GetTextureWidth();
}

int Mass::GetTextureHeight()
{
	return GameObject::GetTextureHeight();
}

int Mass::GetSpriteWidth()
{
	return GameObject::GetSpriteWidth();
}

int Mass::GetSpriteHeight()
{
	return GameObject::GetSpriteHeight();
}

D3DXVECTOR2 Mass::GetSpriteCenter()
{
	return GameObject::GetSpriteCenter();
}

D3DXVECTOR2* Mass::GetSpriteCenterAddress()
{
	return GameObject::GetSpriteCenterAddress();
}

D3DXVECTOR2 Mass::GetScaling()
{
	return GameObject::GetScaling();
}

D3DXVECTOR2* Mass::GetScalingAddress()
{
	return GameObject::GetScalingAddress();
}

RECT Mass::GetDisplayRect()
{
	return GameObject::GetDisplayRect();
}

RECT* Mass::GetDisplayRectAddress()
{
	return GameObject::GetDisplayRectAddress();
}

D3DXVECTOR2 Mass::GetPosition()
{
	return GameObject::GetPosition();
}

D3DXVECTOR2* Mass::GetPositionAddress()
{
	return GameObject::GetPositionAddress();
}

float Mass::GetMass()
{
	return mass;
}

int Mass::GetHp()
{
	return hp;
}

bool Mass::GetConsumed()
{
	return consumed;
}

void Mass::InitDisplayRect()
{
	int rectTop = 0;
	int rectLeft = 0;
	int rectRight = rectLeft + GameObject::GetSpriteWidth();
	int rectBottom = rectTop + GameObject::GetSpriteHeight();

	GameObject::SetDisplayRect(rectTop, rectLeft, rectRight, rectBottom);
}


// Game Loop Methods
void Mass::Update()
{
	if (consumed)
	{
		hp = 0;
		// Set position outside of the screen, to avoid collision with the player
		// -10, -10 to avoid player getting too close to the edge of the screen and mass get consumed again
		SetPosition(-10,10);
		std::cout << "Mass consumed" << endl;
		consumed = false;
	}
}

void Mass::Draw(LPD3DXSPRITE spriteBrush)
{
	D3DXMatrixTransformation2D(this->GetMatrixAddress(), NULL, 0.0f, this->GetScalingAddress(), this->GetSpriteCenterAddress(), 0.0f, this->GetPositionAddress());
	spriteBrush->SetTransform(this->GetMatrixAddress());
	if (this->GetHp() > 0)
	{
		HRESULT hr = spriteBrush->Draw(objectTexture, GetDisplayRectAddress(), NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
		if (FAILED(hr))
		{
			std::cout << "Draw Failed." << endl;
		}
	}
}

void Mass::CleanUp()
{
	GameObject::CleanUp();
}
