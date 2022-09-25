#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

#include "DirectInputManager.h"

/**
 * \brief Manager class for cursor in game
 *
 * This class is responsible for managing the cursor in the game, creates the cursor and handle the cursor's position and it will render the cursor texture to the screen.
 */
class CursorManager
{
private:
    LONG currentXpos;
    LONG currentYpos;
    LPDIRECT3DTEXTURE9 cursorTexture;
    RECT cursorSpriteRect;
    D3DXVECTOR2 cursorPosition;
    LONG cursorX, cursorY;
    DirectInputManager* directInputManager;
    bool showCursor;
public:
    /**
     * \brief Default Constructor for CursorManager
     * \param WindowWidth WindowWidth of the game
     * \param WindowHeight WindowHeight of the game
     * \param directInputManager DirectInputManager pointer to be used for retrieving position of the cursor
     * \param d3dDevice D3DDevice to be used for creating texture 
     */
    CursorManager(int WindowWidth, int WindowHeight, DirectInputManager* directInputManager,
                  IDirect3DDevice9* d3dDevice);
    /**
     * \brief Initialize values of the cursor
     * \param WindowWidth Retrieve from constructor
     * \param WindowHeight Retrieve from constructor
     * \param d3dDevice Retrieve from constructor
     */
    void Init(int WindowWidth, int WindowHeight, IDirect3DDevice9* d3dDevice);
    /**
     * \brief Get Current Mouse Input
     */
    void GetInput();
    /**
     * \brief Render Cursor on the screen
     * \param spriteBrush Sprite brush to be used for rendering
     */
    void Render(LPD3DXSPRITE spriteBrush);
    /**
     * \brief Clean Up cursor
     * Release and set texture to NULL
     */
    void CleanUp();
    /**
     * \brief Get the current position of the cursor
     * \return X axis position
     */
    LONG GetCursorX();
    /**
     * \brief Get the current position of the cursor
     * \return Y axis position
     */
    LONG GetCursorY();
    /**
     * \brief Set the cursor to be show or not
     * \param showCursor Boolean value to determine to show cursor or not, default to true
     */
    void SetShowCursor(bool showCursor);
};
