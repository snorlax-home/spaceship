#pragma once
#include <vector>

#include "GameObject.h"
#include "Mass.h"
//#include "SpaceshipAudioManager.h"
#include "AudioManager.h"
#include "GameSound.h"

class Spaceship : public GameObject
{
private:
	int playerNum;
	int textureRow;
	int textureColumn;
	int spriteFPS; //Is this needed?
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
	//SpaceshipAudioManager *spaceshipAudioManager;
	// std::vector<GameSound*> gameSounds; not sure if this is needed
	GameSound* bounceSound;
	GameSound* collectSound;

public:
	Spaceship();
	~Spaceship();
	
	void Init(int playerNum, int textureWidth, int textureHeight, int textureRow, int textureColumn, int spriteFPS, int maxFrame, int positionX, int positionY,
		float engineForce, float direction, float mass, float rotationSpeed, AudioManager* audioManager);

	// Setters
	void SetTextureWidth(int textureWidth) override;
	void SetTextureHeight(int textureHeight) override;
	void SetTextureRow(int texture_row);
	void SetTextureColumn(int texture_column);
	void SetScaling(float scalingX, float scalingY) override;
	void SetSpriteFPS(int sprite_fps);
	void SetFrameCounter(int frame_counter);
	void SetMaxFrame(int max_frame);
	void SetPosition(D3DXVECTOR2 position) override;
	void SetPosition(float x, float y) override;
	void SetPositionX(float x) override;
	void SetPositionY(float y) override;
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
	void SetMass(float mass) override;
	void SetRotationSpeed(float rotation_speed);
	void SetSpaceshipCollided(bool spaceship_Collided);
	void SetMassCollided(bool mass_Collided);
	void SetWallCollided(bool wall_collided);

	// Getters
	int GetPlayerNum();
	int GetTextureWidth() override;
	int GetTextureHeight() override;
	int GetTextureRow();
	int GetTextureColumn();
	int GetSpriteWidth() override;
	int GetSpriteHeight() override;
	D3DXVECTOR2 GetSpriteCenter() override;
	D3DXVECTOR2 *GetSpriteCenterAddress() override;
	D3DXVECTOR2 GetScaling() override;
	D3DXVECTOR2 *GetScalingAddress() override;
	int GetSpriteFPS();
	int GetFrameCounter();
	int GetMaxFrame();
	RECT GetDisplayRect() override;
	RECT *GetDisplayRectAddress() override;
	D3DXVECTOR2 GetPosition() override;
	D3DXVECTOR2 *GetPositionAddress() override;
	D3DXVECTOR2 GetVelocity();
	D3DXVECTOR2 GetAcceleration();
	float GetEngineForce();
	float GetDirection();
	float GetMass() override;
	float GetRotationSpeed();
	bool GetSpaceshipCollided();
	bool GetMassCollided();
	bool GetWallCollided();

	// Other methods
	void InitDisplayRect();
	bool CircleCollisionDetection(int radiusB, D3DXVECTOR2 positionB);
	void CollisionSpaceship(Spaceship *anotherSpaceship);
	void CollisionMass(Mass *anotherMass);
	void NextFrame(int playerNumber);
	void WindowBounce(int windowWidth, int windowHeight);
	void Move(bool turnLeft, bool turnRight, bool goForward, bool goBackward, float friction);

	// Game Loop Methods
	void Update(bool turnLeft, bool turnRight, bool goForward, bool goBackward, float friction, Spaceship *anotherSpaceship, Mass *massArray[], int arraySize, int windowWidth, int windowHeight);
	void Draw(LPD3DXSPRITE spriteBrush, LPDIRECT3DTEXTURE9 texture);
	void PlaySounds(AudioManager *audioManager);
};
