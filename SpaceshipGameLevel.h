#pragma once
#include "GameLevel.h"
#include "Label.h"
#include "Spaceship.h"
#include "Mass.h"
//#include "SpaceshipLevelAudioManager.h"
#include "GameSound.h"

class SpaceshipGameLevel : public GameLevel
{
private:
    Label* label1;
    Label* label2;
    Spaceship* player1;
    Spaceship* player2;
    Mass* mass1;
    Mass* mass2;
    Mass* mass3;
    int player1Points;
    int player2Points;
    float friction;
    LPD3DXSPRITE spriteBrush;
    LPD3DXSPRITE textBrush;
    HRESULT hr;
    int point;
    Mass* massArray[3];
    bool upKeyPressed;
    bool downKeyPressed;
    bool leftKeyPressed;
    bool rightKeyPressed;
    bool wKeyPressed;
    bool sKeyPressed; 
    bool aKeyPressed;
    bool dKeyPressed;
    bool gameEnd;
    LPDIRECT3DTEXTURE9 playertexture;
    LPDIRECT3DTEXTURE9 massTexture;
    GameSound* backgroundMusic;
    

public:
    SpaceshipGameLevel(AudioManager* audioManager, LPDIRECT3DDEVICE9 d3DDevice, StateMachine* stateMachine,CursorManager* cursorManager,
                       int windowWidth, int windowHeight);
    ~SpaceshipGameLevel() override;
    void InitLevel();
    void GetInput(BYTE*, DIMOUSESTATE) override;
    void PlaySounds();
    void CleanUp();
    void Update(int frameToUpdate) override;
    void RenderGraphics(LPD3DXSPRITE graphicsBrush) override;
    void RenderText(LPD3DXSPRITE textBrush) override;
    void RenderLine() override;
};
