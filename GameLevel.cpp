#include "GameLevel.h"

GameLevel::GameLevel(AudioManager* audioManager)
{
	this->audioManager = audioManager;
}

GameLevel::~GameLevel()
{
}

void GameLevel::InitLevel()
{
}

void GameLevel::GetInput(BYTE, DIMOUSESTATE)
{
}

void GameLevel::Update(BYTE diKeys, DIMOUSESTATE mouseState)
{
	GetInput(diKeys, mouseState);
}

void GameLevel::Render(LPD3DXSPRITE spriteBrush)
{
}

void GameLevel::CleanUp()
{
}
