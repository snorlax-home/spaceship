#include "SpaceshipGameLevel.h"

void SpaceshipGameLevel::InitLevel(int windowWidth, int windowHeight)
{
	srand(time(0));
	hr = D3DXCreateTextureFromFile(GetD3DDevice(), "Assets/practical9.png", &playertexture);
	HRManager("Failed to load player texture.");

	// load mass
	hr = D3DXCreateTextureFromFile(GetD3DDevice(), "Assets/mass.png", &massTexture);
	HRManager("Failed to load mass texture.");

	// Create the players
	player1 = new Spaceship();
	player2 = new Spaceship();

	// Create the masses
	mass1 = new Mass();
	mass2 = new Mass();
	mass3 = new Mass();

	// Create the audio manager
	spaceshipLevelAudioManager = new SpaceshipLevelAudioManager();

	// Initialize players
	player1->Init(1, 64, 64, 2, 2, 10, 1, 600, 300, 1.0, 0, 1, 0.1);
	player2->Init(2, 64, 64, 2, 2, 10, 1, 100, 300, 1.0, 0, 1, 0.1);

	// Initialize masses
	mass1->Init(32, 32, 9, 9, 0, 0, windowWidth, windowHeight, 1, 1);
	mass2->Init(32, 32, 9, 9, 0, 0, windowWidth, windowHeight, 1, 1);
	mass3->Init(32, 32, 9, 9, 0, 0, windowWidth, windowHeight, 1, 1);

	// Initialize the mass array
	massArray = {mass1, mass2, mass3};

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
	spaceshipLevelAudioManager->playBackgroundMusic();

	// Set window width and height
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	gameEnd = false;
}

void SpaceshipGameLevel::GetInput(BYTE diKeys)
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
		if (player1->GetPosition().y > WindowHeight - player1->GetSpriteHeight())
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
		if (player1->GetPosition().x > WindowWidth - player1->GetSpriteWidth())
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
		if (player2->GetPosition().y > WindowHeight - player2->GetSpriteHeight())
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
		if (player2->GetPosition().x > WindowWidth - player2->GetSpriteWidth())
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

void SpaceshipGameLevel::Update(int framesToUpdate)
{
	// update player1 and player 2 for the number of frames to update
	for (int i = 0; i < framesToUpdate; i++)
	{
		player1->Update(aKeyPressed, dKeyPressed, wKeyPressed, sKeyPressed, friction, player2, massArray, 3, windowWidth, windowHeight);
		player2->Update(leftKeyPressed, rightKeyPressed, upKeyPressed, downKeyPressed, friction, player1, massArray, 3, windowWidth, windowHeight);
	}

	if (player1->GetMassCollided() == true)
	{
		player1Points++;
	}

	if (player2->GetMassCollided() == true)
	{
		player2Points++;
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

	if (player1Points == 2 || player2Points == 2)
	{
		gameEnd = true;
	}
}

void SpaceshipGameLevel::Render(LPD3DXSPRITE spriteBrush)
{
	player1->Draw(spriteBrush, playerTexture);
	player2->Draw(spriteBrush, playerTexture);
	mass1->Draw(spriteBrush, massTexture);
	mass2->Draw(spriteBrush, massTexture);
	mass3->Draw(spriteBrush, massTexture);
}

void SpaceshipGameLevel::playSound()
{
	player1->SpaceshipPlaySound();
	player2->SpaceshipPlaySound();
	spaceshipLevelAudioManager->UpdateSound(player1Points + player2Points);
}

void SpaceshipGameLevel::CleanUp()
{
	player1 = NULL;
	player2 = NULL;
	mass1 = NULL;
	mass2 = NULL;
	mass3 = NULL;
	playerTexture = NULL;
	massTexture = NULL;
	spaceshipLevelAudioManager->CleanUp();
	massArray = NULL;
}