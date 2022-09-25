#include "Mass.h"
#include <iostream>

using namespace std;

Mass::Mass()
{
	hp = 0;
	mass = 0;
	consumed = false;
	textureRedValue = 255;
	textureGreenValue = 255;
	textureBlueValue = 255;
	textureColor = D3DCOLOR_XRGB(textureRedValue, textureGreenValue, textureBlueValue);
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
	
	displayRect.top = 0;
	displayRect.left = 0;
	displayRect.right = spriteWidth;
	displayRect.bottom = spriteHeight;
}

// Setters
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
	D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, &scaling, &spriteCenter, 0.0f, &position);
	spriteBrush->SetTransform(&matrix);
	if (this->GetHp() > 0)
	{
		HRESULT hr = spriteBrush->Draw(objectTexture, &displayRect, NULL, NULL, textureColor);
		if (FAILED(hr))
		{
			std::cout << "Draw Failed." << endl;
		}
	}
}

