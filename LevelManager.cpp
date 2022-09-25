#include "LevelManager.h"
#include "GameLevel.h"
LevelManager::LevelManager()
{
}

LevelManager::~LevelManager()
{
    // Clean up levelMap
    for (std::pair<const std::string, GameLevel*> map : levelMap)
    {
        levelMap.erase(map.first);
    }
}

void LevelManager::RegisterLevel(std::string levelName, GameLevel* level)
{
    levelMap[levelName] = level;
}

GameLevel* LevelManager::GetLevel(std::string levelName)
{
    return levelMap[levelName];
}
