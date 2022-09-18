#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
    delete this;
}

void GameObject::Init(char GameObjectType, int textureWidth, int textureHeight, int spriteWidth, int spriteHeight, int displayRectLeft, int displayRectTop, int positionX, int positionY, float mass)
{
    this->gameObjectType = GameObjectType;
    this->textureWidth = textureWidth;
    this->textureHeight = textureHeight;
    this->spriteWidth = spriteWidth;
    this->spriteHeight = spriteHeight;
    this->spriteCenter = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);
    this->scaling = D3DXVECTOR2(1.0f, 1.0f);

    this->displayRect.left = displayRectLeft;
    this->displayRect.top = displayRectTop;
    this->displayRect.right = displayRectLeft + spriteWidth;
    this->displayRect.bottom = displayRectTop + spriteHeight;

    this->position = D3DXVECTOR2(positionX, positionY);
    this->mass = mass;
}

void GameObject::SetGameObjectType(char GameObjectType)
{
    this->gameObjectType = GameObjectType;
}

void GameObject::SetTextureWidth(int textureWidth)
{
    this->textureWidth = textureWidth;
}

void GameObject::SetTextureHeight(int textureHeight)
{
    this->textureHeight = textureHeight;
}

void GameObject::SetSpriteWidth(int spriteWidth)
{
    this->spriteWidth = spriteWidth;
    spriteCenter = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);
}

void GameObject::SetSpriteHeight(int spriteHeight)
{
    this->spriteHeight = spriteHeight;
    spriteCenter = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);
}

void GameObject::SetScaling(float scalingX, float scalingY)
{
    this->scaling = D3DXVECTOR2(scalingX, scalingY);
}

void GameObject::SetDisplayRect(RECT displayRect)
{
    this->displayRect = displayRect;
}

void GameObject::SetDisplayRect(int displayRectLeft, int displayRectTop)
{
    this->displayRect.left = displayRectLeft;
    this->displayRect.top = displayRectTop;
    this->displayRect.right = displayRectLeft + spriteWidth;
    this->displayRect.bottom = displayRectTop + spriteHeight;
}

void GameObject::SetDisplayRectLeft(int displayRectLeft)
{
    this->displayRect.left = displayRectLeft;
    this->displayRect.right = displayRectLeft + spriteWidth;
}

void GameObject::SetDisplayRectTop(int displayRectTop)
{
    this->displayRect.top = displayRectTop;
    this->displayRect.bottom = displayRectTop + spriteHeight;
}

void GameObject::SetPosition(D3DXVECTOR2 position)
{
    this->position = position;
}

void GameObject::SetPosition(float x, float y)
{
    this->position = D3DXVECTOR2(x, y);
}

void GameObject::SetPositionX(float x)
{
    this->position.x = x;
}

void GameObject::SetPositionY(float y)
{
    this->position.y = y;
}

void GameObject::SetMass(float mass)
{
    this->mass = mass;
}


// Getters
char GameObject::GetGameObjectType()
{
    return gameObjectType;
}

int GameObject::GetTextureWidth()
{
    return textureWidth;
}

int GameObject::GetTextureHeight()
{
    return textureHeight;
}

int GameObject::GetSpriteWidth()
{
    return spriteWidth;
}

int GameObject::GetSpriteHeight()
{
    return spriteHeight;
}

D3DXVECTOR2 GameObject::GetSpriteCenter()
{
    return spriteCenter;
}

D3DXVECTOR2 *GameObject::GetSpriteCenterAddress()
{
    return &spriteCenter;
}

D3DXVECTOR2 GameObject::GetScaling()
{
    return scaling;
}

D3DXVECTOR2 *GameObject::GetScalingAddress()
{
    return &scaling;
}

RECT GameObject::GetDisplayRect()
{
    return displayRect;
}

RECT *GameObject::GetDisplayRectAddress()
{
    return &displayRect;
}

D3DXVECTOR2 GameObject::GetPosition()
{
    return position;
}

D3DXVECTOR2 *GameObject::GetPositionAddress()
{
    return &position;
}

D3DXMATRIX* GameObject::GetMatrixAddress()
{
    return &matrix;
}

float GameObject::GetMass()
{
    return mass;
}

// Game Loop Methods
void GameObject::Update()
{
}

void GameObject::Draw()
{
}