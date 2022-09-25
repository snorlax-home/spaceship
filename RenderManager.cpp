#include "RenderManager.h"

#include "CursorManager.h"
#include "Direct3DManager.h"
#include "GameLevel.h"


RenderManager::RenderManager(Direct3DManager* directXManager, CursorManager* cursorManager):
    direct3DManager(directXManager), cursorManager(cursorManager)
{
}

RenderManager::~RenderManager()
{
    delete direct3DManager;
}

void RenderManager::Render(GameLevel* gameLevel)
{
    direct3DManager->PreRender();
    int state = gameLevel->GetRenderState();
    if (CheckRenderGraphics(state))
    {
        gameLevel->RenderMovable(direct3DManager->GetMovableBrush());
    }
    if (CheckRenderText(state))
    {
        gameLevel->RenderStatic(direct3DManager->GetStaticBrush());
    }
    cursorManager->Render(direct3DManager->GetStaticBrush());
    direct3DManager->PostRenderGraphics();
    if (CheckRenderLine(state))
    {
        gameLevel->RenderLine();
    }
    direct3DManager->PostRenderLine();
}
