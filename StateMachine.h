#pragma once
#include <string>

class GameLevel;
class LevelManager;

class StateMachine
{
private:
    LevelManager* levelManager;
    std::string currentState;
public:
    StateMachine(LevelManager* levelManager);
    ~StateMachine();
    void Init();
    GameLevel* GetCurrent();
    void CleanUp();
    void ChangeState(std::string state);
};
