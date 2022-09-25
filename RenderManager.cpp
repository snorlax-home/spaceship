#include "RenderManager.h"

#include "CursorManager.h"
#include "Direct3DManager.h"
#include "GameLevel.h"


RenderManager::RenderManager(Direct3DManager* direct3DManager, CursorManager* cursorManager):
    direct3DManager(direct3DManager), cursorManager(cursorManager)
{
}

RenderManager::~RenderManager()
{
    delete direct3DManager;
}

void RenderManager::Render(GameLevel* gameLevel)
{
    // Prepare for rendering
    direct3DManager->PreRender();

    int state = gameLevel->GetRenderState();
    // Check the game state and render the appropriate scene
    if (CheckRenderMovable(state))
    {
        gameLevel->RenderMovable(direct3DManager->GetMovableBrush());
    }
    if (CheckRenderStatic(state))
    {
        gameLevel->RenderStatic(direct3DManager->GetStaticBrush());
    }
    cursorManager->Render(direct3DManager->GetStaticBrush());

    // Present the rendered scene to the screen
    direct3DManager->PostRenderGraphics();

    // Check render line state
    if (CheckRenderLine(state))
    {
        gameLevel->RenderLine();
    }

    // Present the rendered scene to the screen
    direct3DManager->PostRenderLine();
}
