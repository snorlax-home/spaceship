#pragma once
#include "GameObject.h"
#include "Mass.h"
#include "AudioManager.h"

class Spaceship : public GameObject
{
private:
	int textureRow;
	int textureColumn;
	int spriteFPS;
	int frameCounter;
	int maxFrame;
	D3DXVECTOR2 velocity;
	D3DXVECTOR2 acceleration;
	float engineForce;
	float direction;
	float rotationSpeed;
	bool spaceshipCollided;
	bool massCollided;
	bool wallCollided;

public:
	void Init(int textureWidth, int textureHeight, int textureRow, int textureColumn, int spriteFPS, int maxFrame,
		int animationRectLeft, int animationRectTop, float positionX, float positionY,
		float engineForce, float direction, float mass, float rotationSpeed);

	// Setters
	void SetTextureWidth(int textureWidth);
	void SetTextureHeight(int textureHeight);
	void SetTextureRow(int textureRow);
	void SetTextureColumn(int textureColumn);
	void SetScaling(float scalingX, float scalingY);
	void SetSpriteFPS(int spriteFPS);
	void SetFrameCounter(int frameCounter);
	void SetMaxFrame(int maxFrame);
	void SetDisplayRect(int left, int top);
	void SetDisplayRectLeft(int left);
	void SetDisplayRectTop(int top);
	void SetPosition(D3DXVECTOR2 position);
	void SetPosition(float x, float y);
	void SetPositionX(float x);
	void SetPositionY(float y);
	void SetVelocity(D3DXVECTOR2 velocity);
	void SetVelocity(float x, float y);
	void SetVelocityX(float x);
	void SetVelocityY(float y);
	void SetAcceleration(D3DXVECTOR2 acceleration);
	void SetAcceleration(float x, float y);
	void SetAccelerationX(float x);
	void SetAccelerationY(float y);
	void SetEngineForce(float engineForce);
	void SetDirection(float direction);
	void SetMass(float mass);
	void SetRotationSpeed(float rotationSpeed);
	void SetSpaceshipCollided(bool spaceshipCollided);
	void SetMassCollided(bool massCollided);
	void SetWallCollided(bool wallCollided);

	// Getters
	int GetTextureWidth();
	int GetTextureHeight();
	int GetTextureRow();
	int GetTextureColumn();
	int GetSpriteWidth();
	int GetSpriteHeight();
	D3DXVECTOR2 GetSpriteCenter();
	D3DXVECTOR2* GetSpriteCenterAddress();
	D3DXVECTOR2 GetScaling();
	D3DXVECTOR2* GetScalingAddress();
	int GetSpriteFPS();
	int GetFrameCounter();
	int GetMaxFrame();
	RECT GetDisplayRect();
	RECT* GetDisplayRectAddress();
	D3DXVECTOR2 GetPosition();
	D3DXVECTOR2* GetPositionAddress();
	D3DXVECTOR2 GetVelocity();
	D3DXVECTOR2 GetAcceleration();
	float GetEngineForce();
	float GetDirection();
	float GetMass();
	float GetRotationSpeed();
	bool GetSpaceshipCollided();
	bool GetMassCollided();
	bool GetWallCollided();

	// Other methods
	bool CircleCollisionDetection(int radiusB, D3DXVECTOR2 positionB);
	void CollisionSpaceship(Spaceship* anotherSpaceship);
	void CollisionMass(Mass* anotherMass);
	void NextFrame(int playerNumber);
	void WindowBounce(int windowWidth, int windowHeight);
	void Move(bool turnLeft, bool turnRight, bool goForward, bool goBackward, float friction);
	void SpaceshipPlaySound(AudioManager* audioManager);

    // Game Loop Methods
    void Update();
    void Draw();
};
