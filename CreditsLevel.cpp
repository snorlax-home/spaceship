﻿#include "CreditsLevel.h"

#include "colors.h"
#include "Label.h"
#include "RenderManager.h"
#include "StateMachine.h"
#include "Utils.cpp"

CreditsLevel::CreditsLevel(AudioManager* audioManager, LPDIRECT3DDEVICE9 d3DDevice, StateMachine* stateMachine,
                           CursorManager* cursorManager, int WindowWidth,
                           int WindowHeight):
    GameLevel(audioManager, d3DDevice, stateMachine, cursorManager, "Credits",
              RenderState::Movable, WindowWidth, WindowHeight)
{
}

CreditsLevel::~CreditsLevel()
{
}

void CreditsLevel::AddLabel(std::string content, int width, int height, int startPoint)
{
    labelList.push_back(new Label(this->d3DDevice, content, WHITE(255), D3DXVECTOR2(0, startPoint), width, height,
                                  DT_CENTER | DT_VCENTER | DT_SINGLELINE));
}

void CreditsLevel::InitLevel()
{

    AnimationTimer = 0;
    int width = WindowWidth;
    int height = 30;
    int startPoint = WindowHeight / 2 - 100;
    int spacing = 50;
    AddLabel("===================Credits===================", width, height, startPoint);
    startPoint += spacing;

    AddLabel("Tan Yi Hong", width, height, startPoint);
    startPoint += spacing;
    AddLabel("======================================", width, height, startPoint);
    startPoint += spacing;
    AddLabel("Game State Management", width, height, startPoint);
    startPoint += spacing;
    AddLabel("Game User Interface", width, height, startPoint);
    startPoint += spacing;
    AddLabel("Main Menu Screen", width, height, startPoint);
    startPoint += spacing;
    AddLabel("Game Over Screen", width, height, startPoint);
    startPoint += spacing;
    AddLabel("Credits Screen", width, height, startPoint);
    startPoint += spacing * 2;
    
    AddLabel("Wong Yan Zhi", width, height, startPoint);
    startPoint += spacing;
    AddLabel("======================================", width, height, startPoint);
    startPoint += spacing;
    AddLabel("Animation", width, height, startPoint);
    startPoint += spacing;
    AddLabel("Rendering", width, height, startPoint);
    startPoint += spacing;
    AddLabel("Edge Collision Detection", width, height, startPoint);
    startPoint += spacing;
    AddLabel("Spaceship Game Level", width, height, startPoint);
    startPoint += spacing * 2;
    
    AddLabel("Ong Tun Jiun", width, height, startPoint);
    startPoint += spacing;
    AddLabel("======================================", width, height, startPoint);
    startPoint += spacing;
    AddLabel("Circle Collision Detection & Response", width, height, startPoint);
    startPoint += spacing;
    AddLabel("Audio System", width, height, startPoint);
    startPoint += spacing;
    AddLabel("Sound Manipulation", width, height, startPoint);
    startPoint += spacing;
    AddLabel("Spaceship Game Level", width, height, startPoint);
    startPoint += spacing * 2;
    
    AddLabel("API Involved ", width, height, startPoint);
    startPoint += spacing;
    AddLabel("======================================", width, height, startPoint);
    startPoint += spacing;
    AddLabel("DirectX 3D June 2010 ", width, height, startPoint);
    startPoint += spacing;
    AddLabel("FMOD Core API ", width, height, startPoint);
    startPoint += spacing * 2;
    
    AddLabel("Special Thanks to", width, height, startPoint);
    startPoint += spacing;
    AddLabel("======================================", width, height, startPoint);
    startPoint += spacing;
    AddLabel("Mr. Andrew Tan Khin Huat - Program Leader", width, height, startPoint);
    startPoint += spacing;
    AddLabel("RST2G1 Classmates", width, height, startPoint);
    startPoint += spacing;
    AddLabel("StackOverflow", width, height, startPoint);
    startPoint += spacing * 2;

    AddLabel("===================SPACESHIP MANIA===================", width, height, startPoint);
    startPoint += spacing;
    spacing = 20;
    AddLabel("", width, height, startPoint);
    startPoint += spacing;
    AddLabel("", width, height, startPoint);
    startPoint += spacing;
    AddLabel("", width, height, startPoint);
    startPoint += spacing;
    AddLabel("_", width, height, startPoint);
    startPoint += spacing;
    AddLabel("/ \\", width, height, startPoint);
    startPoint += spacing;
    AddLabel("/ _ \\", width, height, startPoint);
    startPoint += spacing;
    AddLabel("_        | ( ) |        _", width, height, startPoint);
    startPoint += spacing;
    AddLabel("/=\\       /      \\       /=\\", width, height, startPoint);
    startPoint += spacing;
    AddLabel("|=|      |TWO|      |=|", width, height, startPoint);
    startPoint += spacing;
    AddLabel("|=|       \\  _  /       |=|", width, height, startPoint);
    startPoint += spacing;
    AddLabel("|=|       | | | |       |=|", width, height, startPoint);
    startPoint += spacing;
    AddLabel("|=|       | | | |       |=|", width, height, startPoint);
    startPoint += spacing;
    AddLabel("|=|       | | | |       |=|", width, height, startPoint);
    startPoint += spacing;
    AddLabel("|=|     /   | |   \\     |=|", width, height, startPoint);
    startPoint += spacing;
    AddLabel("|=|   /     | |     \\   |=|", width, height, startPoint);
    startPoint += spacing;
    AddLabel("|=/RST2 |_| S1G1\\=|", width, height, startPoint);
    startPoint += spacing;
    AddLabel("|(______________)|", width, height, startPoint);
    startPoint += spacing;
    AddLabel("|=|   |_|__|__|_|   |=|", width, height, startPoint);
    startPoint += spacing;
    AddLabel("|=|       ( )   ( )      |=|", width, height, startPoint);
    startPoint += spacing;
    AddLabel("/===\\                   /===\\", width, height, startPoint);
    startPoint += spacing;
    AddLabel("|||||||                    |||||||", width, height, startPoint);
    startPoint += spacing;
    AddLabel("|||||                      |||||", width, height, startPoint);
    startPoint += spacing;
}

void CreditsLevel::GetInput(BYTE* diKeys, DIMOUSESTATE mouseState)
{
}

void CreditsLevel::Update(int frameToUpdate)
{
    for (int i = 0; i < frameToUpdate; i++)
    {
        AnimationTimer ++;
        if (AnimationTimer % 2 == 0)
        {
            for (int i = 0; i < labelList.size(); i++)
            {
                D3DXVECTOR2 currentLocation = labelList[i]->GetLabelLocation();
                labelList[i]->SetLabelLocation(D3DXVECTOR2(currentLocation.x, currentLocation.y - 5));
            }
        }
    }
    if (AnimationTimer > 1000)
    {
        stateMachine->ChangeState("MainMenu");
    }
}

void CreditsLevel::PlaySounds()
{
}

void CreditsLevel::RenderMovable(LPD3DXSPRITE movableBrush)
{
    for (int i = 0; i < labelList.size(); i++)
    {
        labelList[i]->Render(movableBrush);
    }
}

void CreditsLevel::RenderStatic(LPD3DXSPRITE staticBrush)
{
}

void CreditsLevel::RenderLine()
{
}

void CreditsLevel::CleanUp()
{
    labelList.clear();
}