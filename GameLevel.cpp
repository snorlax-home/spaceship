#include "GameLevel.h"

GameLevel::GameLevel(AudioManager* audioManager, LPDIRECT3DDEVICE9 d3DDevice, GameLevelManager* gameLevelManager)
{
	this->audioManager = audioManager;
	this->d3DDevice = d3DDevice;
	this->gameLevelManager = gameLevelManager;
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

void GameLevel::Update(BYTE diKeys, DIMOUSESTATE mouseState, LONG mouseX, LONG mouseY)
{
	GetInput(diKeys, mouseState);
}

void GameLevel::Render(LPD3DXSPRITE spriteBrush)
{
}

void GameLevel::RenderLine()
{
}

void GameLevel::CleanUp()
{
}
