#pragma once

class GameLevelManager
{
    int currentLevel;
public:
    GameLevelManager();
    int GetCurrentLevel();
    void NextLevel();
    void SetLevel(int level);
};
