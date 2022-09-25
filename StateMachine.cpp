#include "StateMachine.h"

#include <utility>

#include "GameLevel.h"
#include "LevelManager.h"

StateMachine::StateMachine(LevelManager* levelManager)
{
    this->levelManager = levelManager;
}

StateMachine::~StateMachine()
{
    levelManager = nullptr;
}

void StateMachine::Init()
{
    if (!currentState.empty())
    {
        GetCurrent()->InitLevel();
    }
}

GameLevel* StateMachine::GetCurrent()
{
    return levelManager->GetLevel(currentState);
}

void StateMachine::CleanUp()
{
    if (!currentState.empty())
    {
        GetCurrent()->CleanUp();
    }
}

void StateMachine::ChangeState(std::string state)
{
    CleanUp();
    currentState = std::move(state);
    Init();
}
