#pragma once
#include <vector>
#include "GameObject.h"
#include "Mass.h"
#include "AudioManager.h"
#include "GameSound.h"

class Spaceship : public GameObject
{
private:
	int playerNum;
	int textureRow;
	int textureColumn;
	int frameCounter;
	int maxFrame;
	D3DXVECTOR2 velocity;
	D3DXVECTOR2 acceleration;
	float engineForce;
	float direction;
	float rotationSpeed;
	float mass;
	bool massCollided;
	GameSound* bounceSound;
	GameSound* collectSound;
	D3DCOLOR textureColor;

	// Spaceship exclusive methods
	bool CircleCollisionDetection(int radiusB, D3DXVECTOR2 positionB);
	void CollisionSpaceship(Spaceship *anotherSpaceship);
	void CollisionMass(Mass *anotherMass);
	void WindowBounce(int windowWidth, int windowHeight);
	void Move(bool turnLeft, bool turnRight, bool goForward, bool goBackward, float friction);
	void NextFrame(int playerNumber);
	void AlterSoundPan();

public:
	Spaceship();
	~Spaceship() override;
	
	void Init(int playerNum, int textureWidth, int textureHeight, int textureRow, int textureColumn, int maxFrame, int positionX, int positionY,
		float engineForce, float direction, float mass, float rotationSpeed, AudioManager* audioManager);

	// Setters
	void SetTextureWidth(int textureWidth) override;
	void SetTextureHeight(int textureHeight) override;
	void SetTextureRow(int texture_row);
	void SetTextureColumn(int texture_column);
	void SetFrameCounter(int frame_counter);
	void SetMaxFrame(int max_frame);
	void SetVelocity(D3DXVECTOR2 spaceShipVelocity);
	void SetVelocity(float x, float y);
	void SetVelocityX(float x);
	void SetVelocityY(float y);
	void SetAcceleration(D3DXVECTOR2 spaceshipAcceleration);
	void SetAcceleration(float x, float y);
	void SetAccelerationX(float x);
	void SetAccelerationY(float y);
	void SetEngineForce(float engine_Force);
	void SetDirection(float spaceship_Direction);
	void SetMass(float spaceship_Mass);
	void SetRotationSpeed(float rotation_speed);
	void SetMassCollided(bool mass_Collided);

	// Getters
	int GetPlayerNum();
	int GetTextureRow();
	int GetTextureColumn();
	int GetFrameCounter();
	int GetMaxFrame();
	D3DXVECTOR2 GetVelocity();
	D3DXVECTOR2 GetAcceleration();
	float GetEngineForce();
	float GetDirection();
	float GetMass();
	float GetRotationSpeed();
	bool GetMassCollided();
	
	// Game Loop Methods
	void Update(bool turnLeft, bool turnRight, bool goForward, bool goBackward, float friction, Spaceship* anotherSpaceship, std::
	            vector<Mass*>* masses, int windowWidth, int windowHeight);
	void Draw(LPD3DXSPRITE spriteBrush);
	void PlaySounds(AudioManager *audioManager);

	void CleanUp() override;
};
