#pragma once
#include <vector>
#include "Button.h"
#include "GameLevel.h"
#include "Line.h"


class MainMenu : public GameLevel
{
private:
    std::vector<Button> button;
    std::vector<Line> lines;
    LPDIRECT3DTEXTURE9 texture;
public:
    MainMenu(AudioManager* audioManager, LPDIRECT3DDEVICE9 d3DDevice,GameLevelManager* gameLevelManager);
    void InitLevel() override;
    void GetInput(BYTE, DIMOUSESTATE) override;
    void Update(BYTE diKeys, DIMOUSESTATE mouseState, LONG mouseX, LONG mouseY) override;
    void Render(LPD3DXSPRITE) override;
    void RenderLine() override;
    void CleanUp() override;
};
