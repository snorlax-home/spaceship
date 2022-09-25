#include "GameOver.h"
#include "colors.h"
#include "RenderManager.h"
#include "Utils.cpp"

GameOver::GameOver(AudioManager* audioManager, LPDIRECT3DDEVICE9 d3DDevice, StateMachine* stateMachine,
                   CursorManager* cursorManager, int WindowWidth,
                   int WindowHeight): GameLevel(audioManager, d3DDevice, stateMachine, cursorManager,
                                                "GameOver",
                                                RenderState::Movable | RenderState::Static | RenderState::Line,
                                                WindowWidth, WindowHeight)
{
}

GameOver::~GameOver()
{
}

void ctnGame(StateMachine* stateMachine)
{
    PrintLine("Continue Game");
    stateMachine->ChangeState("MainMenu");
};

void exitGame(StateMachine* stateMachine)
{
    PrintLine("Quit Game");
    PostQuitMessage(0);
};

void GameOver::InitLevel()
{
    texture = nullptr;
    D3DXCreateTextureFromFile(d3DDevice, "Assets/gameover.jpg", &texture);
    button.push_back(new Button(&ctnGame, "Continue?", D3DXVECTOR2(100, 400), D3DXVECTOR2(200, 50), WHITE(255),
                                WHITE(255), RED(255), RED(200), GREEN(255), GREEN(205), this->d3DDevice,
                                this->stateMachine));
    button.push_back(new Button(&exitGame, "Quit Game", D3DXVECTOR2(500, 400), D3DXVECTOR2(200, 50), WHITE(255),
                                WHITE(255), RED(255), RED(255), GREEN(255), GREEN(255), this->d3DDevice,
                                this->stateMachine));
}

void GameOver::GetInput(BYTE* byte, DIMOUSESTATE dimousestate)
{
    for (int i = 0; i < button.size(); i++)
    {
        button[i]->GetInput(cursorManager->GetCursorX(), cursorManager->GetCursorY(), dimousestate);
    }
}

void GameOver::Update(int frameToUpdate)
{
    for (int i = 0; i < button.size(); i++)
    {
        button[i]->Update();
    }
}

void GameOver::RenderMovable(LPD3DXSPRITE spriteBrush)
{
    // RECT bgRect;
    // bgRect.left = 0;
    // bgRect.top = 0;
    // bgRect.right = 800;
    // bgRect.bottom = 600;
    // spriteBrush->Draw(texture, &bgRect, NULL, new D3DXVECTOR3(125, 0, 0), D3DCOLOR_XRGB(255, 255, 255));
}

void GameOver::RenderStatic(LPD3DXSPRITE textBrush)
{
    RECT bgRect;
    bgRect.left = 0;
    bgRect.top = 0;
    bgRect.right = 800;
    bgRect.bottom = 600;
    textBrush->Draw(texture, &bgRect, NULL, new D3DXVECTOR3(125, 0, 0), D3DCOLOR_XRGB(255, 255, 255));
    for (int i = 0; i < button.size(); i++)
    {
        button[i]->Render(textBrush);
    }
}

void GameOver::RenderLine()
{
    for (int i = 0; i < button.size(); i++)
    {
        button[i]->RenderLine();
    }
}

void GameOver::CleanUp()
{
    texture->Release();
    texture = nullptr;
}

void GameOver::PlaySounds()
{
}
