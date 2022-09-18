#include "GameLevel.h"

GameLevel::GameLevel(AudioManager* audioManager, UIManager* uiManager, IDirect3DDevice9* d3dDevice)
{
	this->audioManager = audioManager;
	this->uiManager = uiManager;
	this->d3dDevice = d3dDevice;
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

void GameLevel::Render(LPD3DXSPRITE)
{
}

void GameLevel::CleanUp()
{
}
