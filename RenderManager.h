#pragma once

class Direct3DManager;
class CursorManager;
class GameLevel;

/**
 * \brief Render State enumeration
 *
 * To determine the game level requires to run which render function to reduce waste of performance
 */
enum RenderState
{
    /**
     * \brief The game level will be rendering moving objects
     */
    Movable = 0b001,
    /**
     * \brief The game level will be rendering static objects
     */
    Static = 0b010,
    /**
     * \brief The game level will be rendering lines
     */
    Line = 0b100
};

class RenderManager
{
private:
    Direct3DManager* direct3DManager;
    CursorManager* cursorManager;

private:
    /**
     * \brief Check if the game level has movable state
     * \param state State of the game level
     * \return Boolean value of the state
     */
    static bool CheckRenderMovable(int state)
    {
        return (state & RenderState::Movable) == RenderState::Movable;
    }

    /**
     * \brief Check if the game level has static state
     * \param state State of the game level
     * \return Boolean value of the state
     */
    static bool CheckRenderStatic(int state)
    {
        return (state & RenderState::Static) == RenderState::Static;
    }

    /**
         * \brief Check if the game level has line state
         * \param state State of the game level
         * \return Boolean value of the state
         */
    static bool CheckRenderLine(int state)
    {
        return (state & RenderState::Line) == RenderState::Line;
    }

public:
    /**
     * \brief Default constructor
     * \param direct3DManager Pointer of the Direct3DManager 
     * \param cursorManager Pointer of the CursorManager
     */
    RenderManager(Direct3DManager* direct3DManager, CursorManager* cursorManager);
    ~RenderManager();
    /**
     * \brief Render the game level
     * \param gameLevel Pointer of the game level
     */
    void Render(GameLevel* gameLevel);
};
