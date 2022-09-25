#include "GameObject.h"

GameObject::GameObject()
{
    // Initalize variables to 0
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
    // Assign variables with the values passed in
    this->textureWidth = textureWidth;
    this->textureHeight = textureHeight;
    this->spriteWidth = spriteWidth;
    this->spriteHeight = spriteHeight;

    // Calculate the sprite center by dividing the sprite width and height by 2
    this->spriteCenter = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);

    // scaling will be set to original size
    this->scaling = D3DXVECTOR2(1.0f, 1.0f);
    
    this->position = D3DXVECTOR2(positionX, positionY);
}

// Set the texture width
void GameObject::SetTextureWidth(int textureWidth)
{
    this->textureWidth = textureWidth;
}

// Set the texture height
void GameObject::SetTextureHeight(int textureHeight)
{
    this->textureHeight = textureHeight;
}

// Set the sprite width
void GameObject::SetSpriteWidth(int spriteWidth)
{
    this->spriteWidth = spriteWidth;

    // Update the sprite center
    spriteCenter = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);
}

// Set the sprite height
void GameObject::SetSpriteHeight(int spriteHeight)
{
    this->spriteHeight = spriteHeight;

    // Update the sprite center
    spriteCenter = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);
}

// set the scaling
void GameObject::SetScaling(float scalingX, float scalingY)
{
    this->scaling = D3DXVECTOR2(scalingX, scalingY);
}

// Set the DisplayRect using RECT
void GameObject::SetDisplayRect(RECT displayRect)
{
    this->displayRect = displayRect;
}

// Set the DisplayRect using left and top of the rectangle
void GameObject::SetDisplayRect(int displayRectLeft, int displayRectTop)
{
    this->displayRect.top = displayRectTop;
    this->displayRect.left = displayRectLeft;
    this->displayRect.right = displayRectLeft + spriteWidth;
    this->displayRect.bottom = displayRectTop + spriteHeight;
}

// Set position using D3DXVECTOR2
void GameObject::SetPosition(D3DXVECTOR2 position)
{
    this->position = position;
}

// Set position using x and y
void GameObject::SetPosition(float x, float y)
{
    this->position = D3DXVECTOR2(x, y);
}

// Set position.x
void GameObject::SetPositionX(float x)
{
    this->position.x = x;
}

// Set position.y
void GameObject::SetPositionY(float y)
{
    this->position.y = y;
}


void GameObject::SetObjectTextureAddress(LPDIRECT3DTEXTURE9* objectTexture)
{
    this->objectTexture = *objectTexture;
}



// Getters
// Get the texture width
int GameObject::GetTextureWidth()
{
    return textureWidth;
}

// Get the texture height
int GameObject::GetTextureHeight()
{
    return textureHeight;
}

// Get the sprite width
int GameObject::GetSpriteWidth()
{
    return spriteWidth;
}

// Get the sprite height
int GameObject::GetSpriteHeight()
{
    return spriteHeight;
}

// Get the sprite center
D3DXVECTOR2 GameObject::GetSpriteCenter()
{
    return spriteCenter;
}

// Get the scaling
D3DXVECTOR2 GameObject::GetScaling()
{
    return scaling;
}

// Get the DisplayRect
RECT GameObject::GetDisplayRect()
{
    return displayRect;
}


// Get the position
D3DXVECTOR2 GameObject::GetPosition()
{
    return position;
}

// Get texture
LPDIRECT3DTEXTURE9 GameObject::GetObjectTexture()
{
    return objectTexture;
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
    // Release the texture
    objectTexture->Release();
    // set pointer to null
    objectTexture = nullptr;
}


