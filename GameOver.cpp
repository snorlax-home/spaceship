#include "GameOver.h"
#include "colors.h"
#include "Utils.cpp"

GameOver::GameOver(AudioManager* audioManager, LPDIRECT3DDEVICE9 d3DDevice,
                   GameLevelManager* gameLevelManager): GameLevel(audioManager, d3DDevice, gameLevelManager)
{
}

GameOver::~GameOver()
{
}

void ctnGame(GameLevelManager* gameManager)
{
    PrintLine("Continue Game");
    gameManager->SetLevel(0);
};

void exitGame(GameLevelManager* gameManager)
{
    PrintLine("Quit Game");
    PostQuitMessage(0);
};

void GameOver::InitLevel()
{
    texture = nullptr;
    D3DXCreateTextureFromFile(d3DDevice, "Assets/gameover.jpg", &texture);
    button.push_back(Button(&ctnGame, "Continue?", D3DXVECTOR2(100, 400), D3DXVECTOR2(200, 50), WHITE(255),
                            WHITE(255), RED(255), RED(200), GREEN(255), GREEN(205), this->d3DDevice,
                            this->gameLevelManager));
    button.push_back(Button(&exitGame, "Quit Game", D3DXVECTOR2(450, 400), D3DXVECTOR2(200, 50), WHITE(255),
                            WHITE(255), RED(255), RED(255), GREEN(255), GREEN(255), this->d3DDevice,
                            this->gameLevelManager));
}

void GameOver::GetInput(BYTE byte, DIMOUSESTATE dimousestate)
{
    GameLevel::GetInput(byte, dimousestate);
}

void GameOver::Update(BYTE diKeys, DIMOUSESTATE mouseState, LONG mouseX, LONG mouseY)
{
    for (Button b : button)
    {
        b.Update(mouseX, mouseY, mouseState);
    }
}

void GameOver::Render(LPD3DXSPRITE spriteBrush)
{
    RECT bgRect;
    bgRect.left = 0;
    bgRect.top = 0;
    bgRect.right = 800;
    bgRect.bottom = 600;
    spriteBrush->Draw(texture, &bgRect, NULL, new D3DXVECTOR3(125, 0, 0), D3DCOLOR_XRGB(255, 255, 255));
    for (Button b : button)
    {
        b.Render(spriteBrush);
    }
}

void GameOver::RenderLine()
{
    for (Button b : button)
    {
        b.RenderLine();
    }
}

void GameOver::CleanUp()
{
    GameLevel::CleanUp();
}
