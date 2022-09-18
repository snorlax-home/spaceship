#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

#include "AudioManager.h"

class GameLevel {
protected:

	// Managers 
	AudioManager* audioManager;

public:
	GameLevel(AudioManager*);
	~GameLevel();

	virtual void InitLevel();
	virtual void GetInput(BYTE, DIMOUSESTATE);
	virtual void Update(BYTE diKeys, DIMOUSESTATE mouseState);
	virtual void Render(LPD3DXSPRITE);
	virtual void RenderLine();
	virtual void CleanUp();
};