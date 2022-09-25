#include "GameObject.h"

GameObject::GameObject()
{
    textureWidth = 0;
    textureHeight = 0;
    spriteHeight = 0;
    spriteWidth = 0;
}

GameObject::~GameObject()
{
    delete this;
}

void GameObject::Init(int textureWidth, int textureHeight, int spriteWidth, int spriteHeight, int positionX, int positionY)
{
    this->textureWidth = textureWidth;
    this->textureHeight = textureHeight;
    this->spriteWidth = spriteWidth;
    this->spriteHeight = spriteHeight;
    this->spriteCenter = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);
    this->scaling = D3DXVECTOR2(1.0f, 1.0f);
    this->position = D3DXVECTOR2(positionX, positionY);
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

void GameObject::SetDisplayRect(int displayRectLeft, int displayRectTop, int displayRectRight, int displayRectBottom)
{
    this->displayRect.top = displayRectTop;
    this->displayRect.left = displayRectLeft;
    this->displayRect.right = displayRectLeft + spriteWidth;
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


void GameObject::SetObjectTextureAddress(LPDIRECT3DTEXTURE9* objectTexture)
{
    this->objectTexture = *objectTexture;
}



// Getters
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


LPDIRECT3DTEXTURE9 GameObject::GetObjectTexture()
{
    return objectTexture;
}

LPDIRECT3DTEXTURE9* GameObject::GetObjectTextureAddress()
{
    return &objectTexture;
}

// Game Loop Methods
void GameObject::Update()
{
}

void GameObject::Draw()
{
}

void GameObject::PlaySounds()
{
}

void GameObject::CleanUp()
{
    
}


