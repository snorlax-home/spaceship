#pragma once
#include <map>
#include <string>

class GameLevel;

/**
 * \brief Manager class for game levels
 *
 * This class will allows developer to register game level into the levelMap which allows state machine to operate on it later.
 */
class LevelManager
{
private:
    std::map<std::string, GameLevel*> levelMap;
public:
    /**
     * \brief Default constructor for level manager
     */
    LevelManager();
    ~LevelManager();
    /**
     * \brief Register level into levelMap
     * \param levelName Name of game level to be registered and to be used to retrieve back the game level.
     * \param level Pointer of the game level
     */
    void RegisterLevel(std::string levelName, GameLevel* level);
    /**
     * \brief Get a game level pointer with its name
     * \return GameLevel pointer of the game level
     */
    GameLevel* GetLevel(std::string);
};
