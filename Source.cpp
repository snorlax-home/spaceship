#include <vector>

#include "AudioManager.h"
#include "CreditsLevel.h"
#include "CursorManager.h"
#include "DirectInputManager.h"
#include "Direct3DManager.h"
#include "FrameTimer.h"
#include "GameLevel.h"
#include "GameOver.h"
#include "InputManager.h"
#include "LevelManager.h"
#include "StateMachine.h"
#include "MainMenu.h"
#include "RenderManager.h"
#include "SpaceshipGameLevel.h"
#include "WindowsManager.h"

#define WindowWidth 800
#define WindowHeight 600

// Global managers
WindowsManager* windowManager;
DirectInputManager* directInputManager;
Direct3DManager* direct3DManager;
CursorManager* cursorManager;
AudioManager* audioManager;
FrameTimer* timer;
LevelManager* levelManager;
StateMachine* stateMachine;
RenderManager* renderManager;
InputManager* inputManager;


void Init()
{
    windowManager = new WindowsManager("Spaceship Mania", false, WindowWidth, WindowHeight);
    directInputManager = new DirectInputManager(windowManager);
    direct3DManager = new Direct3DManager(windowManager, WindowWidth, WindowHeight);
    cursorManager = new CursorManager(WindowWidth,WindowHeight, directInputManager, direct3DManager->GetDevice());
    levelManager = new LevelManager();
    stateMachine = new StateMachine(levelManager);
    renderManager = new RenderManager(direct3DManager, cursorManager);
    inputManager = new InputManager(directInputManager, cursorManager);

    timer = new FrameTimer();
    timer->Init(60);

    audioManager = new AudioManager();
    audioManager->InitializeAudio();

    MainMenu* mainMenu = new MainMenu(
        audioManager, direct3DManager->GetDevice(), stateMachine, cursorManager, WindowWidth, WindowHeight
    );
    SpaceshipGameLevel* spaceshipGameLevel = new SpaceshipGameLevel(
        audioManager, direct3DManager->GetDevice(), stateMachine, cursorManager, WindowWidth, WindowHeight
    );
    GameOver* gameOver = new GameOver(
        audioManager, direct3DManager->GetDevice(), stateMachine, cursorManager,WindowWidth, WindowHeight);
    CreditsLevel* creditLevel = new CreditsLevel(
        audioManager, direct3DManager->GetDevice(), stateMachine, cursorManager, WindowWidth, WindowHeight
    );
    levelManager->RegisterLevel(mainMenu->GetLevelName(), mainMenu);
    levelManager->RegisterLevel(spaceshipGameLevel->GetLevelName(), spaceshipGameLevel);
    levelManager->RegisterLevel(gameOver->GetLevelName(), gameOver);
    levelManager->RegisterLevel(creditLevel->GetLevelName(), creditLevel);
    stateMachine->ChangeState("MainMenu");
}

void GetInput()
{
    inputManager->GetInput(stateMachine->GetCurrent());
}

void Update()
{
    stateMachine->GetCurrent()->Update(timer->FramesToUpdate());
}

void Render()
{
    renderManager->Render(stateMachine->GetCurrent());
}

void PlaySounds()
{
    audioManager->UpdateSound();
    stateMachine->GetCurrent()->PlaySounds();
}

void CleanUp()
{
    delete stateMachine;
    cursorManager->CleanUp();
    directInputManager->CleanUp();
    direct3DManager->CleanUp();
    windowManager->CleanUpGameWindow();
}

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    Init();
    while (windowManager->WindowIsRunning())
    {
        GetInput();
        Update();
        Render();
        PlaySounds();
    }
    CleanUp();
    return 0;
}
