#pragma once
#include <vector>

#include "GameLevel.h"
#include "GameSound.h"

class Label;

/**
 * \brief Credits level of the game
 *
 * This level is used to display the credits of the game.
 */
class CreditsLevel : public GameLevel
{
private:
    std::vector<Label*> labelList;
    int animationTimer;
    bool moveUp;
    GameSound* backgroundMusic;

    void AddLabel(std::string content, int width, int height, int startPoint);

public:
    CreditsLevel(AudioManager* audioManager, LPDIRECT3DDEVICE9 d3DDevice, StateMachine* stateMachine,
                 CursorManager* cursorManager, int WindowWidth,
                 int WindowHeight);
    ~CreditsLevel() override;
    void InitLevel() override; 
    void GetInput(BYTE* diKeys, DIMOUSESTATE mouseState) override;
    void Update(int frameToUpdate) override;
    void RenderMovable(LPD3DXSPRITE movableBrush) override;
    void RenderStatic(LPD3DXSPRITE staticBrush) override;
    void RenderLine() override;
    void PlaySounds() override;
    void CleanUp() override;
};
