#pragma once

class Direct3DManager;
class CursorManager;
class GameLevel;

enum RenderState
{
    Movable = 0b001,
    Static = 0b010,
    Line = 0b100
};

class RenderManager
{
private:
    Direct3DManager* direct3DManager;
    CursorManager* cursorManager;

    static bool CheckRenderGraphics(int state)
    {
        return (state & RenderState::Movable) == RenderState::Movable;
    }

    static bool CheckRenderText(int state)
    {
        return (state & RenderState::Static) == RenderState::Static;
    }

    static bool CheckRenderLine(int state)
    {
        return (state & RenderState::Line) == RenderState::Line;
    }

public:
    RenderManager(Direct3DManager* directXManager, CursorManager* cursorManager);
    ~RenderManager();
    void Render(GameLevel* gameLevel);
};
