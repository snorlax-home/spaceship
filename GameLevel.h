#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

#include "AudioManager.h"
#include "GameLevelManager.h"

class GameLevel
{
protected:
    // Managers
    LPDIRECT3DDEVICE9 d3DDevice;
    AudioManager* audioManager;
    GameLevelManager* gameLevelManager;

public:
    GameLevel(AudioManager* audioManager, LPDIRECT3DDEVICE9 d3DDevice, GameLevelManager* gameLevelManager);
    ~GameLevel();
    virtual void InitLevel();
    virtual void GetInput(BYTE*, DIMOUSESTATE);
    virtual void Update(BYTE* diKeys, DIMOUSESTATE mouseState, LONG mouseX, LONG mouseY, int frameToUpdate);
    virtual void Render(LPD3DXSPRITE);
    virtual void PlaySounds();
    virtual void RenderLine();
    virtual void CleanUp();
    virtual LPDIRECT3DDEVICE9 GetD3DDevice();

};
