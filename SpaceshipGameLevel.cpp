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

    // Create the players
    player1 = new Spaceship();
    player2 = new Spaceship();

    // Create the masses
    mass1 = new Mass();
    mass2 = new Mass();
    mass3 = new Mass();

    backgroundMusic = new GameSound();
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



    
    textBrush = nullptr;
    hr = D3DXCreateSprite(d3DDevice, &textBrush);
    if (FAILED(hr))
    {
        PrintLine("Failed to create textBrush.");
    }
    // Initialize players
    player1->Init(1, 64, 64, 2, 2, 10, 1, 100, 300, 1.0, 0, 1, 0.1, audioManager);
    player2->Init(2, 64, 64, 2, 2, 10, 1, 600, 300, 1.0, 0, 1, 0.1, audioManager);

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



    // Set window width and height
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;

    gameEnd = false;

    // Initialize background music
    backgroundMusic->Init("Assets/Audio/space-theme.wav",1.0,0.5,0.0, true);

    // Create stream and set it into FMOD::Sound variable in backgroundMusic
    backgroundMusic->SetSound(audioManager->CreateStreams(backgroundMusic->GetSoundFilePath(),backgroundMusic->GetLoop()));
    
    // Play the background music
    audioManager->PlayMusic(backgroundMusic->GetSound(), backgroundMusic->GetVolume(), backgroundMusic->GetPitch(), backgroundMusic->GetPan());
}

void SpaceshipGameLevel::GetInput(BYTE* diKeys, DIMOUSESTATE mouseState)
{
    // player1 movement
    // W key
    if (diKeys[DIK_W] & 0x80)
    {
        wKeyPressed = true;
        PrintLine("W Pressed!");
    }

    // 	S key
    if (diKeys[DIK_S] & 0x80)
    {
        sKeyPressed = true;
        PrintLine("S Pressed!");
    }

    // 	A key
    if (diKeys[DIK_A] & 0x80)
    {
        aKeyPressed = true;
        PrintLine("A Pressed!");
    }

    // 	D key
    if (diKeys[DIK_D] & 0x80)
    {
        dKeyPressed = true;
        PrintLine("D Pressed!");
    }

    // player2 movement
    // Up key
    if (diKeys[DIK_UP] & 0x80)
    {
        upKeyPressed = true;
        PrintLine("Up Pressed!");
    }

    // down key
    if (diKeys[DIK_DOWN] & 0x80)
    {
        downKeyPressed = true;
        PrintLine("Down Pressed!");
    }

    // left key
    if (diKeys[DIK_LEFT] & 0x80)
    {
        leftKeyPressed = true;
        PrintLine("Left Pressed!");
    }

    // 	right key
    if (diKeys[DIK_RIGHT] & 0x80)
    {
        rightKeyPressed = true;
        PrintLine("Right Pressed!");
    }
}

void SpaceshipGameLevel::Update(BYTE* diKeys, DIMOUSESTATE mouseState, LONG mouseX, LONG mouseY, int frameToUpdate)
{
    for (int i = 0; i < frameToUpdate; i++)
    {
        // update player1 and player 2 for the number of frames to update
        player1->Update(aKeyPressed, dKeyPressed, wKeyPressed, sKeyPressed, friction, player2, massArray, 3,
                        windowWidth, windowHeight);
        player2->Update(leftKeyPressed, rightKeyPressed, upKeyPressed, downKeyPressed, friction, player1, massArray, 3,
                        windowWidth, windowHeight);
    }
    if (player1->GetMassCollided())
    {
        player1Points++;
        player1->SetMassCollided(false);
    }

    if (player2->GetMassCollided())
    {
        player2Points++;
        player2->SetMassCollided(false);
    }
    
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
    
    audioManager->AlterMusicChannelPitch(0.5 + ((player1Points + player2Points) * 0.1));
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

void SpaceshipGameLevel::PlaySounds()
{
    player1->PlaySounds(audioManager);
    player2->PlaySounds(audioManager);
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
