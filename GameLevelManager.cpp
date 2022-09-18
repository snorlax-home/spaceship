#include "GameLevelManager.h"

GameLevelManager::GameLevelManager()
{
    currentLevel = 0;
}

int GameLevelManager::GetCurrentLevel()
{
    return currentLevel;
}

void GameLevelManager::NextLevel()
{
    this->currentLevel = this->currentLevel + 1;
}

void GameLevelManager::SetLevel(int level)
{
    this->currentLevel = level;
}

