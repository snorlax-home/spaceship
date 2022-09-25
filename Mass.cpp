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
	// Set mass's position randomly within the window
	// (windowWidth - spriteWidth) and (windowHeight - spriteHeight) are the maximum values for random generation
	// Range for x will be 0 to (windowWidth - spriteWidth)
	// Range for y will be 0 to (windowHeight - spriteHeight)
	int positionX = rand() % (windowWidth - spriteWidth);
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
// Set hp
void Mass::SetHp(int hp)
{
	this->hp = hp;
}

// Set mass
void Mass::SetMass(float newMass)
{
	this->mass = newMass;
}

// Set consumed flag
void Mass::SetConsumed(bool consumed)
{
	this->consumed = consumed;
}

// Getters
// Get hp
int Mass::GetHp()
{
	return hp;
}

// Get mass
float Mass::GetMass()
{
	return mass;
}

// Get consumed flag
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
		HRESULT hr = spriteBrush->Draw(objectTexture, &displayRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
		if (FAILED(hr))
		{
			std::cout << "Draw Failed." << endl;
		}
	}
}

