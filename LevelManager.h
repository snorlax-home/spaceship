#pragma once
#include <map>
#include <string>

class GameLevel;

class LevelManager
{
private:
    std::map<std::string, GameLevel*> levelMap;
public:
    LevelManager();
    ~LevelManager();
    void RegisterLevel(std::string levelName, GameLevel* level);
    GameLevel* GetLevel(std::string);
};
