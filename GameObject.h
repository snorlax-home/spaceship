#pragma once
#include <d3dx9.h>

class GameObject
{
protected:
    int textureWidth;
    int textureHeight;
    int spriteWidth;
    int spriteHeight;
    D3DXMATRIX matrix;
    D3DXVECTOR2 spriteCenter;
    D3DXVECTOR2 scaling;
    RECT displayRect;
    D3DXVECTOR2 position;
    LPDIRECT3DTEXTURE9 objectTexture;
    int textureRedValue;
    int textureGreenValue;
    int textureBlueValue;
    D3DCOLOR textureColor;

public:
    // Constructor
    GameObject();

    // Destructor
    virtual ~GameObject();

    virtual void Init(int textureWidth, int textureHeight, int spriteWidth, int spriteHeight, int positionX, int positionY);

    // Setters
    virtual void SetTextureWidth(int textureWidth);
    virtual void SetTextureHeight(int textureHeight);
    virtual void SetSpriteWidth(int spriteWidth);
    virtual void SetSpriteHeight(int spriteHeight);
    virtual void SetScaling(float scalingX, float scalingY);
    virtual void SetDisplayRect(RECT displayRect);
    virtual void SetDisplayRect(int displayRectLeft, int displayRectTop);
    virtual void SetPosition(D3DXVECTOR2 position);
    virtual void SetPosition(float x, float y);
    virtual void SetPositionX(float x);
    virtual void SetPositionY(float y);
    virtual void SetObjectTextureAddress(LPDIRECT3DTEXTURE9* objectTexture);

    // Getters
    virtual int GetTextureWidth();
    virtual int GetTextureHeight();
    virtual int GetSpriteWidth();
    virtual int GetSpriteHeight();
    virtual D3DXVECTOR2 GetSpriteCenter();
    virtual D3DXVECTOR2 GetScaling();
    virtual RECT GetDisplayRect();
    virtual D3DXVECTOR2 GetPosition();
    virtual LPDIRECT3DTEXTURE9 GetObjectTexture();
    
    // GameLoop Methods
    virtual void Update();
    virtual void Draw();
    virtual void PlaySounds();
    
    virtual void CleanUp();
};
