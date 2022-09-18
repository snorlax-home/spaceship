#include "Mass.h"
#include <iostream>

using namespace std;

void Mass::Init(int textureWidth, int textureHeight, int spriteWidth, int spriteHeight, int displayRectLeft, int displayRectTop, int windowWidth, int windowHeight, float mass, int hp)
{
    int positionX = rand() % (windowWidth - spriteWidth);
    int positionY = rand() % (windowHeight - spriteWidth);

    GameObject::Init('M', textureWidth, textureHeight, spriteWidth, spriteHeight, displayRectLeft, displayRectTop, positionX, positionY, mass);
    this->hp = hp;
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

void Mass::SetDisplayRect(int left, int top)
{
    GameObject::SetDisplayRect(left, top);
}

void Mass::SetDisplayRectLeft(int left)
{
    GameObject::SetDisplayRectLeft(left);
}

void Mass::SetDisplayRectTop(int top)
{
    GameObject::SetDisplayRectTop(top);
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

void Mass::SetMass(float mass)
{
    GameObject::SetMass(mass);
}

void Mass::SetHp(int hp)
{
    this->hp = hp;
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

D3DXVECTOR2 *Mass::GetSpriteCenterAddress()
{
    return GameObject::GetSpriteCenterAddress();
}

D3DXVECTOR2 Mass::GetScaling()
{
    return GameObject::GetScaling();
}

D3DXVECTOR2 *Mass::GetScalingAddress()
{
    return GameObject::GetScalingAddress();
}

RECT Mass::GetDisplayRect()
{
    return GameObject::GetDisplayRect();
}

RECT *Mass::GetDisplayRectAddress()
{
    return GameObject::GetDisplayRectAddress();
}

D3DXVECTOR2 Mass::GetPosition()
{
    return GameObject::GetPosition();
}

D3DXVECTOR2 *Mass::GetPositionAddress()
{
    return GameObject::GetPositionAddress();
}

float Mass::GetMass()
{
    return GameObject::GetMass();
}

int Mass::GetHp()
{
    return hp;
}

// Other methods
void Mass::Consumed()
{
    hp--;
    GameObject::SetPosition(-1, -1);
    cout << "Mass consumed" << endl;
}

// Game Loop Methods
void Mass::Update()
{
}

void Mass::Render()
{
}
