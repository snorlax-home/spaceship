#pragma once
#include <vector>
#include "Button.h"
#include "GameLevel.h"
#include "Line.h"


class MainMenu : public GameLevel
{
private:
    std::vector<Button*> button;
    std::vector<Line> lines;
    LPDIRECT3DTEXTURE9 texture;
public:
    MainMenu(AudioManager* audioManager, LPDIRECT3DDEVICE9 d3DDevice,StateMachine* stateMachine,CursorManager* cursorManager, int WindowWidth, int WindowHeight);
    ~MainMenu() override;
    void InitLevel() override;
    void GetInput(BYTE*, DIMOUSESTATE) override;
    void Update(int frameToUpdate);
    void CleanUp() override;
    void PlaySounds() override;
    void RenderMovable(LPD3DXSPRITE movableBrush) override;
    void RenderStatic(LPD3DXSPRITE staticBrush) override;
    void RenderLine() override;
};
