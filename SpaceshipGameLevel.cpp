#include "SpaceshipGameLevel.h"
#include <ctime>

#include "Colors.h"
#include "RenderManager.h"
#include "StateMachine.h"
#include "Utils.cpp"

SpaceshipGameLevel::SpaceshipGameLevel(AudioManager* audioManager, LPDIRECT3DDEVICE9 d3DDevice,
                                       StateMachine* stateMachine, CursorManager* cursorManager, int WindowWidth,
                                       int WindowHeight): GameLevel(audioManager, d3DDevice,
                                                                    stateMachine, cursorManager,
                                                                    "Spaceship",
                                                                    RenderState::Movable |
                                                                    RenderState::Static, WindowWidth, WindowHeight)
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
    for (int i = 0; i < 15; i++)
    {
        masses.push_back(new Mass());
    }

    backgroundMusic = new GameSound();

    this->label1 = new Label(this->d3DDevice, "Player 1 Score : 0", WHITE(255), D3DXVECTOR2(20, 25), 200, 100,
                             DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    this->label2 = new Label(this->d3DDevice, "Player 2 Score : 0", WHITE(255), D3DXVECTOR2(windowWidth - 220, 25), 200,
                             100,
                             DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    srand(time(0));

    // Create the spaceship textures for the players
    HRESULT hr = D3DXCreateTextureFromFile(GetD3DDevice(), "Assets/spaceships.png", &playerTexture);
    if (FAILED(hr))
    {
        MessageBox(NULL, "Could not load spaceship texture", "Error", MB_OK);
    }

    // Create the mass textures
    hr = D3DXCreateTextureFromFile(GetD3DDevice(), "Assets/mass.png", &massTexture);
    if (FAILED(hr))
    {
        MessageBox(NULL, "Could not load mass texture", "Error", MB_OK);
    }

    // Set Texture into GameObjects
    player1->SetObjectTextureAddress(&playerTexture);
    player2->SetObjectTextureAddress(&playerTexture);
    
    // Initialize players
    player1->Init(1, 64, 64, 2, 2, 1, 100, 300, 1.0, 0, 1, 0.1, audioManager);
    player2->Init(2, 64, 64, 2, 2, 1, 600, 300, 1.0, 0, 1, 0.1, audioManager);

    // Initialize masses
    for (int i = 0; i < masses.size(); i++)
    {
        masses[i]->SetObjectTextureAddress(&massTexture);
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

    /*
     * Init(filePath, volume, pitch, pan, loop)
     * volume is set to 0.5 to avoid music covering the sound effects
     * pitch is set to 0.5 to make it slower as original sound is 130bpm
     */
    backgroundMusic->Init("Assets/Audio/space-theme.wav", 0.5, 0.5, 0.0, true);

    // Create stream and set it into FMOD::Sound variable in backgroundMusic
    backgroundMusic->SetSound(
        audioManager->CreateStreams(backgroundMusic->GetSoundFilePath(), backgroundMusic->GetLoop()));

    // Play the background music
    audioManager->PlayMusic(backgroundMusic->GetSound(), backgroundMusic->GetVolume(), backgroundMusic->GetPitch(),
                            backgroundMusic->GetPan());
}

void SpaceshipGameLevel::PointUpdate()
{
    // Update the points of the players by checking the mass collided flag of the spaceships
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

    // Update the score of the players
    std::string player1Score = "Player 1 Score : " + std::to_string(player1Points);
    std::string player2Score = "Player 2 Score : " + std::to_string(player2Points);
    label1->SetLabelText(player1Score);
    label2->SetLabelText(player2Score);
}

void SpaceshipGameLevel::PointCheck()
{
    // Check if the game is over when all of the masses are collected
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

        for (int i = 0; i < masses.size(); i++)
        {
            masses[i]->Update();
        }
    }
    
    // Set all keys that are pressed to false
    aKeyPressed = false;
    dKeyPressed = false;
    wKeyPressed = false;
    sKeyPressed = false;

    leftKeyPressed = false;
    rightKeyPressed = false;
    upKeyPressed = false;
    downKeyPressed = false;

    // Update the points of the players
    PointUpdate();

    /*
     * Alter the pitch of the background music
     * minimum will always be 0 even if there are no points
     * how much the pitch will be altered is based on the points and the number of masses
     * if there are 2 masses, each point will increase pitch by 0.25
     * if there are 5 masses, each point will increase pitch by 0.1
     * Maximum pitch will be capped at 1.0
     * Achieved by using masses.size() * 2 as the divisor
     * when all masses are collected, it will be masses.size() / masses.size() * 2, which will be 0.5
     * Therefore, the maximum pitch will always be 1.0
     */
    audioManager->AlterMusicChannelPitch(0.5 + float(player1Points + player2Points) / float(masses.size() * 2));

    PointCheck();
}

void SpaceshipGameLevel::RenderMovable(LPD3DXSPRITE spriteBrush)
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
    // Call play sound function for player1 and player2
    player1->PlaySounds(audioManager);
    player2->PlaySounds(audioManager);
}


void SpaceshipGameLevel::RenderStatic(LPD3DXSPRITE spriteBrush)
{
    label1->Render(spriteBrush);
    label2->Render(spriteBrush);
}

void SpaceshipGameLevel::RenderLine()
{
}

void SpaceshipGameLevel::CleanUp()
{
    // Pause the background music
    audioManager->PauseMusicChannel();
    // Clean up the background music object
    backgroundMusic->CleanUp();
    // Assign the pointer to NULL
    backgroundMusic = nullptr;

    // Clean up the spaceship objects
    player1->CleanUp();
    player2->CleanUp();

    // Assign the pointers to NULL
    player1 = nullptr;
    player2 = nullptr;

    // Clean up the mass objects and assign pointers to NULL
    for (int i = 0; i < masses.size(); i++)
    {
        masses[i]->CleanUp();
        masses[i] = nullptr;
    }
    // Clear the vector
    masses.clear();
    // Free the memory by shrinking the vector
    masses.shrink_to_fit();

    // Release textures
    playerTexture->Release();
    massTexture->Release();

    // Assign the pointers to NULL
    playerTexture = nullptr;
    massTexture = nullptr;
}
