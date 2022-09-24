#include <vector>

#include "AudioManager.h"
#include "colors.h"
#include "CursorManager.h"
#include "DirectInputManager.h"
#include "DirectXManager.h"
#include "FrameTimer.h"
#include "GameLevel.h"
#include "GameLevelManager.h"
#include "GameOver.h"
#include "MainMenu.h"
#include "SpaceshipGameLevel.h"
#include "WindowsManager.h"


#define WindowWidth 800
#define WindowHeight 600

// Global managers
WindowsManager* windowManager;
DirectInputManager* directInputManager;
DirectXManager* directXManager;
CursorManager* cursorManager;
AudioManager* audioManager;
FrameTimer* timer;

// Game Levels
std::vector<GameLevel*> gameLevels;
GameLevelManager* gameLevelManager;



void GetInput()
{
    directInputManager->GetInput();
    cursorManager->GetInput();
    gameLevels[gameLevelManager->GetCurrentLevel()]->GetInput(directInputManager->GetKeyState(),
                                                              directInputManager->GetMouseState());
}

void Init()
{
    timer = new FrameTimer();
    timer->Init(60);
    audioManager = new AudioManager();
    audioManager->InitializeAudio();
    gameLevelManager = new GameLevelManager();

    MainMenu* mainMenu = new MainMenu(
        audioManager, directXManager->GetDevice(), gameLevelManager
    );
    SpaceshipGameLevel* spaceshipGameLevel = new SpaceshipGameLevel(
        audioManager, directXManager->GetDevice(), gameLevelManager, WindowWidth, WindowHeight
    );
    GameOver* gameOver = new GameOver(
        audioManager, directXManager->GetDevice(), gameLevelManager);
    gameLevels.push_back(mainMenu);
    gameLevels.push_back(spaceshipGameLevel);
    gameLevels.push_back(gameOver);
    for (int i = 0; i < gameLevels.size(); i++)
    {
        gameLevels[i]->InitLevel();
    }
}

void Update(int framesToUpdate)
{
    gameLevels[gameLevelManager->GetCurrentLevel()]->Update(directInputManager->GetKeyState(),
                                                            directInputManager->GetMouseState(),
                                                            cursorManager->GetCursorX(), cursorManager->GetCursorY(),
                                                            framesToUpdate);
}

void Render()
{
    directXManager->PreRender();
    gameLevels[gameLevelManager->GetCurrentLevel()]->Render(directXManager->GetSpriteBrush());
    cursorManager->Render(directXManager->GetSpriteBrush());
    directXManager->PostRenderGraphics();
    gameLevels[gameLevelManager->GetCurrentLevel()]->RenderLine();
    directXManager->PostRenderLine();
}

void PlaySounds()
{
    audioManager->UpdateSound();
    gameLevels[gameLevelManager->GetCurrentLevel()]->PlaySounds();

}

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    windowManager = new WindowsManager("Spaceship Mania", false, WindowWidth, WindowHeight);
    directInputManager = new DirectInputManager(windowManager);
    directXManager = new DirectXManager(windowManager, WindowWidth, WindowHeight);
    cursorManager = new CursorManager(WindowWidth,WindowHeight, directInputManager, directXManager->GetDevice());

    Init();
    while (windowManager->WindowIsRunning())
    {
        if (gameLevels.empty() || gameLevelManager->GetCurrentLevel() >= gameLevels.size())
        {
            break;
        }
        GetInput();
        Update(timer->FramesToUpdate());
        Render();
        PlaySounds();
    }
    while (!gameLevels.empty())
    {
        gameLevels[0]->CleanUp();
        gameLevels.erase(gameLevels.begin());
    }

    cursorManager->CleanUp();
    directInputManager->CleanUp();
    directXManager->CleanUp();
    windowManager->CleanUpGameWindow();

    return 0;
}
