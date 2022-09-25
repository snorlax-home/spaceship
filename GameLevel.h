#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <string>

#include "CursorManager.h"

class AudioManager;
class StateMachine;

class GameLevel
{
protected:
    // Managers
    LPDIRECT3DDEVICE9 d3DDevice;
    AudioManager* audioManager;
    StateMachine* stateMachine;
    CursorManager* cursorManager;
    std::string gameLevelName;
    int renderState;
    int windowWidth;
    int windowHeight;


public:
    GameLevel(AudioManager* audioManager, LPDIRECT3DDEVICE9 d3DDevice, StateMachine* stateMachine,
              CursorManager* cursorManager,
              std::string gameLevelName, int renderState, int WindowWidth, int WindowHeight);
    virtual ~GameLevel();
    virtual void InitLevel();

    // Getters
    virtual LPDIRECT3DDEVICE9 GetD3DDevice();
    virtual AudioManager* GetAudioManager();
    virtual int GetRenderState();
    virtual std::string GetLevelName();

    // Game loop methods
    virtual void GetInput(BYTE* diKeys, DIMOUSESTATE mouseState);
    virtual void Update(int frameToUpdate);
    virtual void PlaySounds();
    virtual void RenderMovable(LPD3DXSPRITE movableBrush);
    virtual void RenderStatic(LPD3DXSPRITE staticBrush);
    virtual void RenderLine();
    
    virtual void CleanUp();
};
