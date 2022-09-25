#pragma once

class DirectInputManager;
class CursorManager;
class GameLevel;

class InputManager
{
private:
    DirectInputManager* directInputManager;
    CursorManager* cursorManager;
public:
    InputManager(DirectInputManager* directInputManager, CursorManager* cursorManager);
    ~InputManager();
    void GetInput(GameLevel* gameLevel);
};
