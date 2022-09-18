#include "SpaceshipGameLevel.h"
#include <ctime>

#include "colors.h"
#include "Utils.cpp"

SpaceshipGameLevel::SpaceshipGameLevel(AudioManager* audioManager, LPDIRECT3DDEVICE9 d3DDevice,
                                       GameLevelManager* gameLevelManager, int windowWidth,
                                       int windowHeight): GameLevel(audioManager, d3DDevice,
                                                                    gameLevelManager)
{
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
}

void SpaceshipGameLevel::InitLevel()
{
    this->label1 = new Label(this->d3DDevice, "Player 1 Score : 0", WHITE(255), D3DXVECTOR2(20, 20), 200, 100,
                             DT_CENTER);
    this->label2 = new Label(this->d3DDevice, "Player 2 Score : 0", WHITE(255), D3DXVECTOR2(windowWidth - 220, 20), 200,
                             100,
                             DT_CENTER);
    srand(time(0));
    hr = D3DXCreateTextureFromFile(GetD3DDevice(), "Assets/practical9.png", &playertexture);
    // HRManager("Failed to load player texture.");

    // load mass
    hr = D3DXCreateTextureFromFile(GetD3DDevice(), "Assets/mass.png", &massTexture);
    // HRManager("Failed to load mass texture.");

    // Create the players
    player1 = new Spaceship();
    player2 = new Spaceship();

    // Create the masses
    mass1 = new Mass();
    mass2 = new Mass();
    mass3 = new Mass();

    // Create the audio manager
    spaceshipLevelAudioManager = new SpaceshipLevelAudioManager();
    textBrush = nullptr;
    hr = D3DXCreateSprite(d3DDevice, &textBrush);
    if (FAILED(hr))
    {
        PrintLine("Failed to create textBrush.");
    }
    // Initialize players
    player1->Init(1, 64, 64, 2, 2, 10, 1, 600, 300, 1.0, 0, 1, 0.1);
    player2->Init(2, 64, 64, 2, 2, 10, 1, 100, 300, 1.0, 0, 1, 0.1);

    // Initialize masses
    mass1->Init(32, 32, 9, 9, this->windowWidth, this->windowHeight, 1, 1);
    mass2->Init(32, 32, 9, 9, this->windowWidth, this->windowHeight, 1, 1);
    mass3->Init(32, 32, 9, 9, this->windowWidth, this->windowHeight, 1, 1);

    // Initialize the mass array
    massArray[0] = mass1;
    massArray[1] = mass2;
    massArray[2] = mass3;

    // Initialize player point
    player1Points = 0;
    player2Points = 0;

    // Initialize friction
    friction = 0.05;

    // Set keys to false
    upKeyPressed = false;
    downKeyPressed = false;
    leftKeyPressed = false;
    rightKeyPressed = false;
    wKeyPressed = false;
    sKeyPressed = false;
    aKeyPressed = false;
    dKeyPressed = false;

    // Initialize audio manager and load Sounds
    spaceshipLevelAudioManager->InitializeAudio();
    spaceshipLevelAudioManager->LoadSounds();

    // Play the background music
    spaceshipLevelAudioManager->PlayBackgroundMusic();

    // Set window width and height
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;

    gameEnd = false;
}

void SpaceshipGameLevel::GetInput(BYTE* diKeys, DIMOUSESTATE mouseState)
{
    //  player1 movement
    // Up key
    if (diKeys[DIK_UP] & 0x80)
    {
        if (player1->GetPosition().y == 0)
        {
            upKeyPressed = false;
        }
        else
        {
            upKeyPressed = true;
            PrintLine("Up Pressed!");
        }
    }

    // down key
    if (diKeys[DIK_DOWN] & 0x80)
    {
        if (player1->GetPosition().y > this->windowHeight - player1->GetSpriteHeight())
        {
            downKeyPressed = false;
        }
        else
        {
            downKeyPressed = true;
            PrintLine("Down Pressed!");
        }
    }

    // left key
    if (diKeys[DIK_LEFT] & 0x80)
    {
        if (player1->GetPosition().x == 0)
        {
            leftKeyPressed = false;
        }
        else
        {
            leftKeyPressed = true;
            PrintLine("Left Pressed!");
        }
    }

    // 	right key
    if (diKeys[DIK_RIGHT] & 0x80)
    {
        if (player1->GetPosition().x > this->windowWidth - player1->GetSpriteWidth())
        {
            rightKeyPressed = false;
        }
        else
        {
            rightKeyPressed = true;
            PrintLine("Right Pressed!");
        }
    }

    // player2 movement
    // W key
    if (diKeys[DIK_W] & 0x80)
    {
        if (player2->GetPosition().y == 0)
        {
            wKeyPressed = false;
        }
        else
        {
            wKeyPressed = true;
            PrintLine("W Pressed!");
        }
    }

    // 	S key
    if (diKeys[DIK_S] & 0x80)
    {
        if (player2->GetPosition().y > this->windowHeight - player2->GetSpriteHeight())
        {
            sKeyPressed = false;
        }
        else
        {
            sKeyPressed = true;
            PrintLine("S Pressed!");
        }
    }

    // 	A key
    if (diKeys[DIK_A] & 0x80)
    {
        if (player2->GetPosition().x == 0)
        {
            aKeyPressed = false;
        }
        else
        {
            aKeyPressed = true;
            PrintLine("A Pressed!");
        }
    }

    // 	D key
    if (diKeys[DIK_D] & 0x80)
    {
        if (player2->GetPosition().x > this->windowWidth - player2->GetSpriteWidth())
        {
            dKeyPressed = false;
        }
        else
        {
            dKeyPressed = true;
            PrintLine("D Pressed!");
        }
    }
}

void SpaceshipGameLevel::Update(BYTE* diKeys, DIMOUSESTATE mouseState, LONG mouseX, LONG mouseY, int frameToUpdate)
{
    for (int i = 0; i < frameToUpdate; i++)
    {
        // update player1 and player 2 for the number of frames to update
        player1->Update(leftKeyPressed, rightKeyPressed, upKeyPressed, downKeyPressed, friction, player2, massArray, 3,
                        windowWidth, windowHeight);
        player2->Update(aKeyPressed, dKeyPressed, wKeyPressed, sKeyPressed, friction, player1, massArray, 3,
                        windowWidth, windowHeight);
    }
    if (player1->GetMassCollided() == true)
    {
        player1Points++;
        player1->SpaceshipPlaySound();
        player1->SetMassCollided(false);
    }

    if (player2->GetMassCollided() == true)
    {
        player2Points++;
        player2->SpaceshipPlaySound();
        player2->SetMassCollided(false);
    }

    // player1
    aKeyPressed = false;
    dKeyPressed = false;
    wKeyPressed = false;
    sKeyPressed = false;

    // player2
    leftKeyPressed = false;
    rightKeyPressed = false;
    upKeyPressed = false;
    downKeyPressed = false;
    if (player1Points != 0)
    {
        if (player1Points == 1)
        {
            label1->SetLabelText("Player 1 Score : 1");
        }
        else if (player1Points == 2)
        {
            label1->SetLabelText("Player 1 Score : 2");
        }
    }
    if (player2Points != 0)
    {
        if (player2Points == 1)
        {
            label2->SetLabelText("Player 2 Score : 1");
        }
        else if (player2Points == 2)
        {
            label2->SetLabelText("Player 2 Score : 2");
        }
    }
    if (player1Points == 2 || player2Points == 2)
    {
        gameEnd = true;
        gameLevelManager->NextLevel();
    }
}

void SpaceshipGameLevel::Render(LPD3DXSPRITE spriteBrush)
{
    textBrush->Begin(D3DXSPRITE_ALPHABLEND);
    player1->Draw(textBrush, playertexture);
    player2->Draw(textBrush, playertexture);
    mass1->Draw(textBrush, massTexture);
    mass2->Draw(textBrush, massTexture);
    mass3->Draw(textBrush, massTexture);
    textBrush->End();
    label1->Render(spriteBrush);
    label2->Render(spriteBrush);
}

void SpaceshipGameLevel::playSound()
{
    spaceshipLevelAudioManager->UpdateSound(player1Points + player2Points);
}

void SpaceshipGameLevel::CleanUp()
{
    player1 = NULL;
    player2 = NULL;
    mass1 = NULL;
    mass2 = NULL;
    mass3 = NULL;
    playertexture = NULL;
    massTexture = NULL;
}
