#pragma once
#include "GameObject.h"

class Mass : public GameObject
{
private:
	int hp;
	float mass;
	bool consumed;

public:
	Mass();
	~Mass();

	void Init(int textureWidth, int textureHeight, int spriteWidth, int spriteHeight, int WindowWidth, int windowHeight, float mass, int massHp);
	// Setters
	void SetMass(float newMass);
	void SetHp(int hp);
	void SetConsumed(bool consumed);
	// Getters
	float GetMass();
	int GetHp();
	bool GetConsumed();

	// Game Loop Methods
	void Update() override;
	void Draw(LPD3DXSPRITE spriteBrush);
};
