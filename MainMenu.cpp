#include "MainMenu.h"
#include "colors.h"

void startGame(GameLevelManager* gameManager)
{
    gameManager->NextLevel();
}

void quitGame(GameLevelManager* gameManager)
{
    PostQuitMessage(0);
}

MainMenu::MainMenu(AudioManager* audioManager, LPDIRECT3DDEVICE9 d3DDevice, GameLevelManager* gameLevelManager):
    GameLevel(audioManager, d3DDevice, gameLevelManager)
{
}

void MainMenu::InitLevel()
{
    texture = nullptr;
    D3DXCreateTextureFromFile(d3DDevice, "Assets/main.jpg", &texture);

    button.push_back(Button(&startGame, "Start Game", D3DXVECTOR2(300, 300), D3DXVECTOR2(200, 50), WHITE(255),
                            WHITE(255), GREEN(255), GREEN(255),BLUE(255), BLUE(255), this->d3DDevice,
                            this->gameLevelManager));
    button.push_back(Button(&quitGame, "Quit Game", D3DXVECTOR2(300, 400), D3DXVECTOR2(200, 50), WHITE(255),
                            WHITE(255), GREEN(255), GREEN(255),RED(255), RED(255), this->d3DDevice,
                            this->gameLevelManager));
    // Spaceship vertex
    std::vector<D3DXVECTOR2> vertexS = {
        D3DXVECTOR2(50, 60),
        D3DXVECTOR2(110, 60),
        D3DXVECTOR2(110, 80),
        D3DXVECTOR2(70, 80),
        D3DXVECTOR2(70, 100),
        D3DXVECTOR2(110, 100),
        D3DXVECTOR2(110, 160),
        D3DXVECTOR2(50, 160),
        D3DXVECTOR2(50, 140),
        D3DXVECTOR2(90, 140),
        D3DXVECTOR2(90, 120),
        D3DXVECTOR2(50, 120),
        D3DXVECTOR2(50, 60),
    };

    std::vector<D3DXVECTOR2> vertexP1 = {
        D3DXVECTOR2(120, 60),
        D3DXVECTOR2(180, 60),
        D3DXVECTOR2(180, 120),
        D3DXVECTOR2(140, 120),
        D3DXVECTOR2(140, 160),
        D3DXVECTOR2(120, 160),
        D3DXVECTOR2(120, 60),
    };

    std::vector<D3DXVECTOR2> vertexP2 = {
        D3DXVECTOR2(140, 80),
        D3DXVECTOR2(160, 80),
        D3DXVECTOR2(160, 100),
        D3DXVECTOR2(140, 100),
        D3DXVECTOR2(140, 80),
    };

    std::vector<D3DXVECTOR2> vertexA1 = {
        D3DXVECTOR2(190, 60),
        D3DXVECTOR2(250, 60),
        D3DXVECTOR2(250, 160),
        D3DXVECTOR2(230, 160),
        D3DXVECTOR2(230, 120),
        D3DXVECTOR2(210, 120),
        D3DXVECTOR2(210, 160),
        D3DXVECTOR2(190, 160),
        D3DXVECTOR2(190, 60),
    };

    std::vector<D3DXVECTOR2> vertexA2 = {
        D3DXVECTOR2(210, 80),
        D3DXVECTOR2(230, 80),
        D3DXVECTOR2(230, 100),
        D3DXVECTOR2(210, 100),
        D3DXVECTOR2(210, 80),
    };

    std::vector<D3DXVECTOR2> vertexC = {
        D3DXVECTOR2(260, 60),
        D3DXVECTOR2(320, 60),
        D3DXVECTOR2(320, 80),
        D3DXVECTOR2(280, 80),
        D3DXVECTOR2(280, 140),
        D3DXVECTOR2(320, 140),
        D3DXVECTOR2(320, 160),
        D3DXVECTOR2(260, 160),
        D3DXVECTOR2(260, 60),
    };

    std::vector<D3DXVECTOR2> vertexE = {
        D3DXVECTOR2(330, 60),
        D3DXVECTOR2(390, 60),
        D3DXVECTOR2(390, 80),
        D3DXVECTOR2(350, 80),
        D3DXVECTOR2(350, 100),
        D3DXVECTOR2(390, 100),
        D3DXVECTOR2(390, 120),
        D3DXVECTOR2(350, 120),
        D3DXVECTOR2(350, 140),
        D3DXVECTOR2(390, 140),
        D3DXVECTOR2(390, 160),
        D3DXVECTOR2(330, 160),
        D3DXVECTOR2(330, 60),
    };

    std::vector<D3DXVECTOR2> vertexS2 = {
        D3DXVECTOR2(400, 60),
        D3DXVECTOR2(460, 60),
        D3DXVECTOR2(460, 80),
        D3DXVECTOR2(420, 80),
        D3DXVECTOR2(420, 100),
        D3DXVECTOR2(460, 100),
        D3DXVECTOR2(460, 160),
        D3DXVECTOR2(400, 160),
        D3DXVECTOR2(400, 140),
        D3DXVECTOR2(440, 140),
        D3DXVECTOR2(440, 120),
        D3DXVECTOR2(400, 120),
        D3DXVECTOR2(400, 60),
    };

    std::vector<D3DXVECTOR2> vertexH = {
        D3DXVECTOR2(470, 60),
        D3DXVECTOR2(490, 60),
        D3DXVECTOR2(490, 100),
        D3DXVECTOR2(510, 100),
        D3DXVECTOR2(510, 60),
        D3DXVECTOR2(530, 60),
        D3DXVECTOR2(530, 160),
        D3DXVECTOR2(510, 160),
        D3DXVECTOR2(510, 120),
        D3DXVECTOR2(490, 120),
        D3DXVECTOR2(490, 160),
        D3DXVECTOR2(470, 160),
        D3DXVECTOR2(470, 60),
    };

    std::vector<D3DXVECTOR2> vertexI = {
        D3DXVECTOR2(540, 60),
        D3DXVECTOR2(600, 60),
        D3DXVECTOR2(600, 80),
        D3DXVECTOR2(580, 80),
        D3DXVECTOR2(580, 140),
        D3DXVECTOR2(600, 140),
        D3DXVECTOR2(600, 160),
        D3DXVECTOR2(540, 160),
        D3DXVECTOR2(540, 140),
        D3DXVECTOR2(560, 140),
        D3DXVECTOR2(560, 80),
        D3DXVECTOR2(540, 80),
        D3DXVECTOR2(540, 60),
    };

    std::vector<D3DXVECTOR2> vertexP3 = {
        D3DXVECTOR2(610, 60),
        D3DXVECTOR2(670, 60),
        D3DXVECTOR2(670, 120),
        D3DXVECTOR2(630, 120),
        D3DXVECTOR2(630, 160),
        D3DXVECTOR2(610, 160),
        D3DXVECTOR2(610, 60),
    };

    std::vector<D3DXVECTOR2> vertexP4 = {
        D3DXVECTOR2(630, 80),
        D3DXVECTOR2(650, 80),
        D3DXVECTOR2(650, 100),
        D3DXVECTOR2(630, 100),
        D3DXVECTOR2(630, 80),
    };

    lines = {
        Line(d3DDevice, vertexS.size(), vertexS, WHITE(255)),
        Line(d3DDevice, vertexP1.size(), vertexP1, WHITE(255)),
        Line(d3DDevice, vertexP2.size(), vertexP2, WHITE(255)),
        Line(d3DDevice, vertexA1.size(), vertexA1, WHITE(255)),
        Line(d3DDevice, vertexA2.size(), vertexA2, WHITE(255)),
        Line(d3DDevice, vertexC.size(), vertexC, WHITE(255)),
        Line(d3DDevice, vertexE.size(), vertexE, WHITE(255)),
        Line(d3DDevice, vertexS2.size(), vertexS2, WHITE(255)),
        Line(d3DDevice, vertexH.size(), vertexH, WHITE(255)),
        Line(d3DDevice, vertexI.size(), vertexI, WHITE(255)),
        Line(d3DDevice, vertexP3.size(), vertexP3, WHITE(255)),
        Line(d3DDevice, vertexP4.size(), vertexP4, WHITE(255)),
    };
}

void MainMenu::GetInput(BYTE byte, DIMOUSESTATE dimousestate)
{
    GameLevel::GetInput(byte, dimousestate);
}

void MainMenu::Update(BYTE diKeys, DIMOUSESTATE mouseState, LONG mouseX, LONG mouseY)
{
    for (Button b : button)
    {
        b.Update(mouseX, mouseY, mouseState);
    }
    GameLevel::Update(diKeys, mouseState, mouseX, mouseY);
}

void MainMenu::Render(LPD3DXSPRITE spriteBrush)
{
    RECT bgRect;
    bgRect.left = 0;
    bgRect.top = 0;
    bgRect.right = 800;
    bgRect.bottom = 600;
    spriteBrush->Draw(texture, &bgRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
    for (Button b : button)
    {
        b.Render(spriteBrush);
    }
}

void MainMenu::RenderLine()
{
    for (Button b : button)
    {
        b.RenderLine();
    }
    for (int i = 0; i < lines.size(); i++)
    {
        lines[i].Render();
    }
}

void MainMenu::CleanUp()
{
    GameLevel::CleanUp();
}
