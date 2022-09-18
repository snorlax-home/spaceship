#pragma once
#include "GameLevel.h"
#include "Spaceship.h"
#include "Mass.h"
#include "SpaceshipLevelAudioManager.h"

class SpaceshipGameLevel : public GameLevel
{
private:
	Spaceship *player1;
	Spaceship *player2;
	Mass *mass1;
	Mass *mass2;
	Mass *mass3;
	SpaceshipLevelAudioManager *spaceshipLevelAudioManager;
	int player1Points;
	int player2Points;
	float friction;
	LPD3DXSPRITE spriteBrush;
	HRESULT hr;
	int point;
	Mass *massArray[3];
	bool upKeyPressed;
	bool downKeyPressed;
	bool leftKeyPressed;
	bool rightKeyPressed;
	bool wKeyPressed;
	bool sKeyPressed;
	bool aKeyPressed;
	bool dKeyPressed;
	int windowWidth;
	int windowHeight;
	bool gameEnd;

public:
	void InitLevel(int windowWidth, int winHeight);
	void GetInput(LPDIRECTINPUTDEVICE8 dInputKeyboardDevice) override;
	void Update(int framesToUpdate);
	void Render(LPD3DXSPRITE spriteBrush);
	void playSound();
	void CleanUp();
};
