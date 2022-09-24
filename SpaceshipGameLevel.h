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
    
    std::vector<Mass*> masses;
    
    int player1Points;
    int player2Points;
    float friction;
    LPD3DXSPRITE spriteBrush;
    LPD3DXSPRITE textBrush;
    HRESULT hr; // Is this appropriate here?
    int point;
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
    GameSound* backgroundMusic;
    

public:
    SpaceshipGameLevel(AudioManager* audioManager, LPDIRECT3DDEVICE9 d3DDevice, GameLevelManager* gameLevelManager,
                       int windowWidth, int windowHeight);
    void InitLevel() override;
    void PointUpdate();
    void PointCheck();

    // Game loop methods
    void GetInput(BYTE*, DIMOUSESTATE) override;
    void Update(BYTE* diKeys, DIMOUSESTATE mouseState, LONG mouseX, LONG mouseY, int frameToUpdate) override;
    void Render(LPD3DXSPRITE spriteBrush) override;
    void PlaySounds() override;

    void CleanUp() override;
};
