#pragma once
#include "Button.h"
#include "GameLevel.h"

class GameOver : public GameLevel
{
private:
    std::vector<Button> button;
    LPDIRECT3DTEXTURE9 texture;
public:
    GameOver(AudioManager* audioManager, LPDIRECT3DDEVICE9 d3DDevice,  GameLevelManager* gameLevelManager);
    ~GameOver();
    void InitLevel() override;
    void GetInput(BYTE, DIMOUSESTATE) override;
    void Update(BYTE diKeys, DIMOUSESTATE mouseState, LONG mouseX, LONG mouseY) override;
    void Render(LPD3DXSPRITE) override;
    void RenderLine() override;
    void CleanUp() override;
};
