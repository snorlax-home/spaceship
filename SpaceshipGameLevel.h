#pragma once
#include "GameLevel.h"
#include "Label.h"
#include "Spaceship.h"
#include "Mass.h"
#include "GameSound.h"

class SpaceshipGameLevel : public GameLevel
{
private:
    Label* label1;
    Label* label2;

    Spaceship* player1;
    Spaceship* player2;

    std::vector<Mass*> masses;

    int player1Points;
    int player2Points;
    float friction;
    HRESULT hr; // TODO: Is this appropriate here?
    bool upKeyPressed;
    bool downKeyPressed;
    bool leftKeyPressed;
    bool rightKeyPressed;
    bool wKeyPressed;
    bool sKeyPressed;
    bool aKeyPressed;
    bool dKeyPressed;
    bool gameEnd;
    LPDIRECT3DTEXTURE9 playerTexture;
    LPDIRECT3DTEXTURE9 massTexture;
    GameSound* backgroundMusic;


public:
    SpaceshipGameLevel(AudioManager* audioManager, LPDIRECT3DDEVICE9 d3DDevice, StateMachine* stateMachine,
                       CursorManager* cursorManager,
                       int windowWidth, int windowHeight);
    ~SpaceshipGameLevel() override;
    void InitLevel();
    void PointUpdate();
    void PointCheck();
    
    void RenderMovable(LPD3DXSPRITE graphicsBrush) override;
    void RenderStatic(LPD3DXSPRITE textBrush) override;
    void RenderLine() override;

    // Game Loop methods
    void GetInput(BYTE*, DIMOUSESTATE) override;
    void Update(int frameToUpdate) override;
    void PlaySounds() override;

    void CleanUp() override;
};
