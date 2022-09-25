#include "InputManager.h"
#include "DirectInputManager.h"
#include "CursorManager.h"
#include "GameLevel.h"

InputManager::InputManager(DirectInputManager* directInputManager, CursorManager* cursorManager):
    directInputManager(directInputManager), cursorManager(cursorManager)
{
}

InputManager::~InputManager()
{
}

void InputManager::GetInput(GameLevel* gameLevel)
{
    directInputManager->GetInput();
    cursorManager->GetInput();
    gameLevel->GetInput(directInputManager->GetKeyState(), directInputManager->GetMouseState());
}
