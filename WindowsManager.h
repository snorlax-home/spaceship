#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

/**
 * \brief Manager class for game window
 *
 * This class is responsible to create and set up the game window, check whether the game should be ended
 */
class WindowsManager
{
private:
    HWND m_hWnd;
    MSG msg;
    WNDCLASS wndClass;
    LPCSTR windowName;
    bool showCursor;
    int windowWidth;
    int windowHeight;
public:
    /**
     * \brief Default constructor for WindowsManager
     * \param windowName The name of the window
     * \param showCursor Whether the cursor should be shown or not
     * \param windowWidth The width of the window
     * \param windowHeight The height of the window
     */
    WindowsManager(LPCSTR windowName, bool showCursor, int windowWidth, int windowHeight);
    /**
     * \brief WindowProcedure for the game window
     * \param hWnd Handle to the window
     * \param message Current message to be process
     * \param wParam Parameter for the message
     * \param lParam Parameter for the message
     */
    static LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    /**
     * \brief Create the game window
     */
    void CreateGameWindow();
    /**
     * \brief Check whether game loop should be ended
     * \return Boolean value
     */
    bool WindowIsRunning();
    /**
     * \brief Clean up the game window
     */
    void CleanUpGameWindow();
    /**
     * \brief Get the handle to the game window
     * \return HWND handle to the game window
     */
    HWND GetHandle();
};
