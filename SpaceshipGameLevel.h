#pragma once
#include "GameLevel.h"
#include "Label.h"
#include "Spaceship.h"
#include "Mass.h"
#include "SpaceshipLevelAudioManager.h"

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
    SpaceshipLevelAudioManager* spaceshipLevelAudioManager;
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
    int windowWidth;
    int windowHeight;
    bool gameEnd;
    LPDIRECT3DTEXTURE9 playertexture;
    LPDIRECT3DTEXTURE9 massTexture;

public:
    SpaceshipGameLevel(AudioManager* audioManager, LPDIRECT3DDEVICE9 d3DDevice, GameLevelManager* gameLevelManager,
                       int windowWidth, int windowHeight);
    void InitLevel();
    void GetInput(BYTE*, DIMOUSESTATE) override;
    void Update(BYTE* diKeys, DIMOUSESTATE mouseState, LONG mouseX, LONG mouseY, int frameToUpdate);
    void Render(LPD3DXSPRITE spriteBrush);
    void playSound();
    void CleanUp();
};
