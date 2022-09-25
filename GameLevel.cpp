#include "GameLevel.h"

#include <stdexcept>

#include "AudioManager.h"
#include "StateMachine.h"

GameLevel::GameLevel(AudioManager* audioManager, LPDIRECT3DDEVICE9 d3DDevice, StateMachine* stateMachine,
                     CursorManager* cursorManager, std::string gameLevelName, int renderState, int WindowWidth,
                     int WindowHeight):
    audioManager(audioManager), d3DDevice(d3DDevice),
    stateMachine(stateMachine), cursorManager(cursorManager), WindowWidth(WindowWidth),
    WindowHeight(WindowHeight), gameLevelName(gameLevelName), renderState(
        renderState)
{
}

GameLevel::~GameLevel()
= default;

void GameLevel::InitLevel()
{
    throw std::logic_error("The method or operation is not implemented.");
}

void GameLevel::PlaySounds()
{
    throw std::logic_error("The method or operation is not implemented.");
}

void GameLevel::RenderGraphics(LPD3DXSPRITE graphicsBrush)
{
    throw std::logic_error("The method or operation is not implemented.");
}

void GameLevel::RenderText(LPD3DXSPRITE textBrush)
{
    throw std::logic_error("The method or operation is not implemented.");
}

void GameLevel::RenderLine()
{
    throw std::logic_error("The method or operation is not implemented.");
}

void GameLevel::GetInput(BYTE*, DIMOUSESTATE)
{
    throw std::logic_error("The method or operation is not implemented.");
}

void GameLevel::Update(int frameToUpdate)
{
    throw std::logic_error("The method or operation is not implemented.");
}


void GameLevel::CleanUp()
{
    throw std::logic_error("The method or operation is not implemented.");
}

LPDIRECT3DDEVICE9 GameLevel::GetD3DDevice()
{
    return d3DDevice;
}

AudioManager* GameLevel::GetAudioManager()
{
    return audioManager;
}

int GameLevel::GetRenderState()
{
    return renderState;
}

std::string GameLevel::GetLevelName()
{
    return gameLevelName;
}
