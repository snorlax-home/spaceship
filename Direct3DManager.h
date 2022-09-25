#pragma once
#include <d3d9.h>
#include <d3dx9.h>

#include "WindowsManager.h"
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
/**
 * \brief Manager class for DirectX 9 graphics.
 *
 * This class is a singleton and is used to manage DirectX 9 graphics.
 * It will provides sprite brush for both movable object and static object.
 */
class Direct3DManager
{
private:
    IDirect3DDevice9* d3dDevice;
    LPD3DXSPRITE movableBrush;
    LPD3DXSPRITE staticBrush;
    WindowsManager* windowsManager;
public:
    /**
     * \brief Default constructor for Direct3D Manager.
     * \param windowsManager Window manager to retrieve window handle
     * \param windowWidth Width of game window
     * \param windowHeight Height of game window
     */
    Direct3DManager(WindowsManager* windowsManager, int windowWidth, int windowHeight);
    /**
     * \brief Initialize Direct3D Manager.
     * \param windowWidth Game window width
     * \param windowHeight Game window height
     */
    void Init(int windowWidth, int windowHeight);
    /**
     * \brief Preparation before rendering.
     */
    void PreRender();
    /**
     * \brief End rendering graphics
     */
    void PostRenderGraphics();
    /**
     * \brief End rendering line
     */
    void PostRenderLine();
    /**
     * \brief Clean Up function to release brushes and d3dDevice and set the to NULL
     */
    void CleanUp();
    /**
     * \brief Get brush for movable object
     * \return Long pointer to movable brush
     */
    LPD3DXSPRITE GetMovableBrush();
    /**
     * \brief Get brush for static object
     * \return Long pointer to static brush
     */
    LPD3DXSPRITE GetStaticBrush();
    /**
     * \brief Get d3dDevice
     * \return Pointer to d3dDevice
     */
    IDirect3DDevice9* GetDevice();
};
