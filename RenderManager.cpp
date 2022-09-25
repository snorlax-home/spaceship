#include "RenderManager.h"

#include "CursorManager.h"
#include "DirectXManager.h"
#include "GameLevel.h"

RenderManager::RenderManager(DirectXManager* directXManager, CursorManager* cursorManager):
    directXManager(directXManager), cursorManager(cursorManager)
{
}

RenderManager::~RenderManager()
{
    delete directXManager;
}

void RenderManager::Render(GameLevel* gameLevel)
{
    directXManager->PreRender();
    int state = gameLevel->GetRenderState();
    if (CheckRenderGraphics(state))
    {
        gameLevel->RenderMovable(directXManager->GetGraphicsBrush());
    }
    if (CheckRenderText(state))
    {
        gameLevel->RenderStatic(directXManager->GetTextBrush());
    }
    cursorManager->Render(directXManager->GetTextBrush());
    directXManager->PostRenderGraphics();
    if (CheckRenderLine(state))
    {
        gameLevel->RenderLine();
    }
    directXManager->PostRenderLine();
}
