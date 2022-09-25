#pragma once
#include <string>

class GameLevel;
class LevelManager;

/**
 * \brief StateMachine to manage different levels
 *
 * This class will keep track of what levels should be display and handle now
 * and provide functions to switch between levels.
 */
class StateMachine
{
private:
    LevelManager* levelManager;
    std::string currentState;
public:
    /**
     * \brief Default constructor for StateMachine
     * \param levelManager Level manager to access the list of game level registered to the game
     */
    StateMachine(LevelManager* levelManager);
    ~StateMachine();
    /**
     * \brief Initialize current game level
     */
    void Init();
    /**
     * \brief Get the current game level
     * \return Return the current game level
     */
    GameLevel* GetCurrent();
    /**
     * \brief Clean up the state engine
     */
    void CleanUp();
    /**
     * \brief Change the current game level to the desire game level
     * \param state Name of the game level registered in the level manager
     */
    void ChangeState(std::string state);
};
