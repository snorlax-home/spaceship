#pragma once
#include <vector>

#include "GameLevel.h"

class Label;

class CreditsLevel : public GameLevel
{
private:
    std::vector<Label*> labelList;
    int AnimationTimer;
    bool moveUp;

public:
    CreditsLevel(AudioManager* audioManager, LPDIRECT3DDEVICE9 d3DDevice, StateMachine* stateMachine,
                 CursorManager* cursorManager, int WindowWidth,
                 int WindowHeight);
    ~CreditsLevel() override;
    void AddLabel(std::string content, int width, int height, int startPoint);
    void InitLevel() override;
    void GetInput(BYTE* diKeys, DIMOUSESTATE mouseState) override;
    void Update(int frameToUpdate) override;
    void PlaySounds() override;
    void RenderMovable(LPD3DXSPRITE movableBrush) override;
    void RenderStatic(LPD3DXSPRITE staticBrush) override;
    void RenderLine() override;
    void CleanUp() override;
};
