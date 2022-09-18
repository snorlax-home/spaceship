#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

#include "AudioManager.h"
#include "UIManager.h"

class GameLevel {
protected:

	// Interface
	IDirect3DDevice9* d3dDevice;

	// Managers 
	AudioManager* audioManager;
	UIManager* uiManager;

	// Input
	BYTE diKeys[256];
	DIMOUSESTATE mouseState;

public:
	GameLevel(AudioManager*, UIManager*, IDirect3DDevice9*);
	~GameLevel();

	virtual void InitLevel();
	virtual void GetInput(BYTE, DIMOUSESTATE);
	virtual void Update(BYTE diKeys, DIMOUSESTATE mouseState);
	virtual void Render(LPD3DXSPRITE);
	virtual void CleanUp();
};