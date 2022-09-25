#pragma once

class DirectInputManager;
class CursorManager;
class GameLevel;

/**
 * \brief Manager class for input activities
 *
 * This class is responsible for managing input activities. It is responsible for providing value of input and also manage the cursor of the game.
 */
class InputManager
{
private:
    DirectInputManager* directInputManager;
    CursorManager* cursorManager;
public:
    /**
     * \brief Default constructor of InputManager
     * \param directInputManager Pointer of DirectInputManager
     * \param cursorManager Pointer of CursorManager
     */
    InputManager(DirectInputManager* directInputManager, CursorManager* cursorManager);
    ~InputManager();
    /**
     * \brief Execute get input function of the game level
     * \param gameLevel Game level pointer for getting input
     */
    void GetInput(GameLevel* gameLevel);
};
