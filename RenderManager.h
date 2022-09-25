#pragma once

class DirectXManager;
class CursorManager;
class GameLevel;

enum RenderState
{
    Graphics = 0b001,
    Text = 0b010,
    Line = 0b100
};

class RenderManager
{
private:
    DirectXManager* directXManager;
    CursorManager* cursorManager;

private:
    static bool CheckRenderGraphics(int state)
    {
        return (state & RenderState::Graphics) == RenderState::Graphics;
    }

    static bool CheckRenderText(int state)
    {
        return (state & RenderState::Text) == RenderState::Text;
    }

    static bool CheckRenderLine(int state)
    {
        return (state & RenderState::Line) == RenderState::Line;
    }

public:
    RenderManager(DirectXManager* directXManager, CursorManager* cursorManager);
    ~RenderManager();
    void Render(GameLevel* gameLevel);
};
