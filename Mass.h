#pragma once
#include "GameObject.h"

class Mass : public GameObject
{
private:
    int hp;

public:
    void Init(int textureWidth, int textureHeight, int spriteWidth, int spriteHeight, int displayRectLeft, int displayRectTop, int WindowWidth, int windowHeight, float mass, int hp);
    // Setters
    void SetTextureWidth(int textureWidth);
    void SetTextureHeight(int textureHeight);
    void SetSpriteWidth(int spriteWidth);
    void SetSpriteHeight(int spriteHeight);
    void SetScaling(float scalingX, float scalingY);
    void SetDisplayRect(int left, int top);
    void SetDisplayRectLeft(int left);
    void SetDisplayRectTop(int top);
    void SetPosition(D3DXVECTOR2 position);
    void SetPosition(float x, float y);
    void SetPositionX(float x);
    void SetPositionY(float y);
    void SetMass(float mass);
    void SetHp(int hp);
    // Getters
    int GetTextureWidth();
    int GetTextureHeight();
    int GetSpriteWidth();
    int GetSpriteHeight();
    D3DXVECTOR2 GetSpriteCenter();
    D3DXVECTOR2 *GetSpriteCenterAddress();
    D3DXVECTOR2 GetScaling();
    D3DXVECTOR2 *GetScalingAddress();
    RECT GetDisplayRect();
    RECT *GetDisplayRectAddress();
    D3DXVECTOR2 GetPosition();
    D3DXVECTOR2 *GetPositionAddress();
    float GetMass();
    int GetHp();
    // Other methods
    void Consumed();

    // Game Loop Methods
    void Update();
    void Draw(LPD3DXSPRITE spriteBrush, LPDIRECT3DTEXTURE9 texture);
};
