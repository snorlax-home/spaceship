#pragma once
#include <d3dx9.h>

class GameObject
{
private:
    char GameObjectType;
    int textureWidth;
    int textureHeight;
    int spriteWidth;
    int spriteHeight;
    D3DXVECTOR2 spriteCenter;
    D3DXVECTOR2 scaling;
    RECT displayRect;
    D3DXVECTOR2 position;
    float mass;

public:
    // Constructor
    GameObject();

    // Destructor
    ~GameObject();

    virtual void Init(char GameObjectType, int textureWidth, int textureHeight, int spriteWidth, int spriteHeight, int displayRectLeft, int displayRectTop, int positionX, int positionY, float mass);

    // Setters
    virtual void SetGameObjectType(char GameObjectType);
    virtual void SetTextureWidth(int textureWidth);
    virtual void SetTextureHeight(int textureHeight);
    virtual void SetSpriteWidth(int spriteWidth);
    virtual void SetSpriteHeight(int spriteHeight);
    virtual void SetScaling(float scalingX, float scalingY);
    virtual void SetDisplayRect(RECT displayRect);
    virtual void SetDisplayRect(int displayRectLeft, int displayRectTop);
    virtual void SetDisplayRectLeft(int displayRectLeft);
    virtual void SetDisplayRectTop(int displayRectTop);
    virtual void SetPosition(D3DXVECTOR2 position);
    virtual void SetPosition(float x, float y);
    virtual void SetPositionX(float x);
    virtual void SetPositionY(float y);
    virtual void SetMass(float mass);

    // Getters
    virtual char GetGameObjectType();
    virtual int GetTextureWidth();
    virtual int GetTextureHeight();
    virtual int GetSpriteWidth();
    virtual int GetSpriteHeight();
    virtual D3DXVECTOR2 GetSpriteCenter();
    virtual D3DXVECTOR2 *GetSpriteCenterAddress();
    virtual D3DXVECTOR2 GetScaling();
    virtual D3DXVECTOR2 *GetScalingAddress();
    virtual RECT GetDisplayRect();
    virtual RECT *GetDisplayRectAddress();
    virtual D3DXVECTOR2 GetPosition();
    virtual D3DXVECTOR2 *GetPositionAddress();
    virtual float GetMass();

    // GameLoop Methods
    virtual void Update();
    virtual void Draw();
};
