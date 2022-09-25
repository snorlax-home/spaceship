#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

class WindowsManager
{
private:
    HWND m_hWnd;
    MSG msg;
    WNDCLASS wndClass;
    LPCSTR windowName;

    // Actual message handler
    // virtual LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
    bool showCursor;
    int windowWidth;
    int windowHeight;
public:
    // Static message handler to be used for WNDCLASS structure
    // static LRESULT stWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    WindowsManager(LPCSTR windowName, bool showCursor, int windowWidth, int windowHeight);
    static LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    void CreateGameWindow();
    bool WindowIsRunning();
    void CleanUpGameWindow();
    HWND GetHandle();
};
