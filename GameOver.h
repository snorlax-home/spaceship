#pragma once
#include "Button.h"
#include "GameLevel.h"
#include "GameSound.h"

/**
 * \brief Game Over level
 *
 * This is the level to be show after the game is over.
 * This level allows you to quit the game or restart the game.
 */
class GameOver : public GameLevel
{
private:
    std::vector<Button*> button; 
    LPDIRECT3DTEXTURE9 texture;
    GameSound* backgroundMusic;
public:
    GameOver(AudioManager* audioManager, LPDIRECT3DDEVICE9 d3DDevice, StateMachine* stateMachine,
             CursorManager* cursorManager, int WindowWidth, int WindowHeight);
    ~GameOver();
    void InitLevel() override;
    void GetInput(BYTE*, DIMOUSESTATE) override;
    void Update(int frameToUpdate) override;
    void CleanUp() override;
    void PlaySounds() override;
    void RenderMovable(LPD3DXSPRITE graphicsBrush) override;
    void RenderStatic(LPD3DXSPRITE textBrush) override;
    void RenderLine() override;
};
