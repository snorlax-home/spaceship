#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <string>

#include "CursorManager.h"

class AudioManager;
class StateMachine;

/**
 * \brief Game Level class
 *
 * This is the base class for all the game levels in the game
 * This class is responsible for the following:
 * - Loading and unloading of the level
 * - Updating the level
 * - Rendering the level
 * - Handling input for the level
 * - Handling the level's audio
 */
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
