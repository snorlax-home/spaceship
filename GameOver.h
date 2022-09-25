#pragma once
#include "Button.h"
#include "GameLevel.h"

class GameOver : public GameLevel
{
private:
    std::vector<Button*> button;
    LPDIRECT3DTEXTURE9 texture;
public:
    GameOver(AudioManager* audioManager, LPDIRECT3DDEVICE9 d3DDevice,StateMachine* stateMachine,CursorManager* cursorManager, int WindowWidth, int WindowHeight);
    ~GameOver();
    void InitLevel() override;
    void GetInput(BYTE*, DIMOUSESTATE) override;
    void Update(int frameToUpdate) override;
    void CleanUp() override;
    void PlaySounds() override;
    void RenderGraphics(LPD3DXSPRITE graphicsBrush) override;
    void RenderText(LPD3DXSPRITE textBrush) override;
    void RenderLine() override;
};
