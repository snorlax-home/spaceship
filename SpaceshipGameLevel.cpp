#include "SpaceshipGameLevel.h"
#include <ctime>

#include "colors.h"
#include "RenderManager.h"
#include "StateMachine.h"
#include "Utils.cpp"

SpaceshipGameLevel::SpaceshipGameLevel(AudioManager* audioManager, LPDIRECT3DDEVICE9 d3DDevice,
                                       StateMachine* stateMachine, CursorManager* cursorManager, int WindowWidth,
                                       int WindowHeight): GameLevel(audioManager, d3DDevice,
                                                                    stateMachine, cursorManager,
                                                                    "Spaceship",
                                                                    RenderState::Graphics |
                                                                    RenderState::Text, WindowWidth, WindowHeight)
{

}

SpaceshipGameLevel::~SpaceshipGameLevel()
{
    delete this;
}


void SpaceshipGameLevel::InitLevel()
{
    // Create the players
    player1 = new Spaceship();
    player2 = new Spaceship();

    // Create the masses and add them to the vector
    for (int i = 0; i < 10; i++)
    {
        masses.push_back(new Mass());
    }

    backgroundMusic = new GameSound();
    
    this->label1 = new Label(this->d3DDevice, "Player 1 Score : 0", WHITE(255), D3DXVECTOR2(20, 20), 200, 100,
                             DT_CENTER);
    this->label2 = new Label(this->d3DDevice, "Player 2 Score : 0", WHITE(255), D3DXVECTOR2(windowWidth - 220, 20), 200,
                             100,
                             DT_CENTER);
    srand(time(0));
    hr = D3DXCreateTextureFromFile(GetD3DDevice(), "Assets/spaceships.png", &playerTexture);
    // HRManager("Failed to load player texture.");

    // load mass
    hr = D3DXCreateTextureFromFile(GetD3DDevice(), "Assets/mass.png", &massTexture);
    // HRManager("Failed to load mass texture.");

    // Set Texture into GameObjects
    player1->SetObjectTextureAddress(&playerTexture);
    player2->SetObjectTextureAddress(&playerTexture);

    for (int i = 0; i < masses.size(); i++)
    {
        masses[i]->SetObjectTextureAddress(&massTexture);
    }
    
    // Initialize players
    player1->Init(1, 64, 64, 2, 2, 1, 100, 300, 1.0, 0, 1, 0.1, audioManager);
    player2->Init(2, 64, 64, 2, 2, 1, 600, 300, 1.0, 0, 1, 0.1, audioManager);

    // Initialize masses
    for (int i = 0; i < masses.size(); i++)
    {
        masses[i]->Init(32, 32, 9, 9, this->windowWidth, this->windowHeight, 1, 1);
    }

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

    gameEnd = false;

    // Initialize background music
    backgroundMusic->Init("Assets/Audio/space-theme.wav", 1.0, 0.5, 0.0, true);

    // Create stream and set it into FMOD::Sound variable in backgroundMusic
    backgroundMusic->SetSound(
        audioManager->CreateStreams(backgroundMusic->GetSoundFilePath(), backgroundMusic->GetLoop()));

    // Play the background music
    audioManager->PlayMusic(backgroundMusic->GetSound(), backgroundMusic->GetVolume(), backgroundMusic->GetPitch(),
                            backgroundMusic->GetPan());
}

void SpaceshipGameLevel::PointUpdate()
{
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
}

void SpaceshipGameLevel::PointCheck()
{
    std::string player1Score = "Player 1 Score : " + std::to_string(player1Points);
    std::string player2Score = "Player 2 Score : " + std::to_string(player2Points);
    label1->SetLabelText(player1Score);
    label2->SetLabelText(player2Score);
    if (player1Points + player2Points == masses.size())
    {
        gameEnd = true;
        stateMachine->ChangeState("GameOver");
    }
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

void SpaceshipGameLevel::Update(int frameToUpdate)
{
    for (int i = 0; i < frameToUpdate; i++)
    {
        // update player1 and player 2 for the number of frames to update
        player1->Update(aKeyPressed, dKeyPressed, wKeyPressed, sKeyPressed, friction, player2, &masses,
                        windowWidth, windowHeight);
        player2->Update(leftKeyPressed, rightKeyPressed, upKeyPressed, downKeyPressed, friction, player1, &masses,
                        windowWidth, windowHeight);
    }

    for (int i = 0; i < masses.size(); i++)
    {
        masses[i]->Update();
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

    PointUpdate();

    audioManager->AlterMusicChannelPitch(0.5 + float(player1Points + player2Points) / float(masses.size() * 2));

    PointCheck();
}

void SpaceshipGameLevel::RenderGraphics(LPD3DXSPRITE spriteBrush)
{
    player1->Draw(spriteBrush);
    player2->Draw(spriteBrush);
    for (int i = 0; i < masses.size(); i++)
    {
        masses[i]->Draw(spriteBrush);
    }
}

void SpaceshipGameLevel::PlaySounds()
{
    player1->PlaySounds(audioManager);
    player2->PlaySounds(audioManager);
}


void SpaceshipGameLevel::RenderText(LPD3DXSPRITE spriteBrush)
{
    label1->Render(spriteBrush);
    label2->Render(spriteBrush);
}

void SpaceshipGameLevel::RenderLine()
{
}

void SpaceshipGameLevel::CleanUp()
{
    audioManager->PauseMusicChannel();
    backgroundMusic->CleanUp();
    backgroundMusic = nullptr;
    
    player1->CleanUp();
    player2->CleanUp();
    player1 = nullptr;
    player2 = nullptr;
    
    for (int i = 0; i < masses.size(); i++)
    {
        masses[i]->CleanUp();
        masses[i] = nullptr;
    }
    masses.clear();
    masses.shrink_to_fit();
    
    // TODO: clean up the label
    //label1->CleanUp();
    
    playerTexture->Release();
    massTexture->Release();
    playerTexture = nullptr;
    massTexture = nullptr;
}