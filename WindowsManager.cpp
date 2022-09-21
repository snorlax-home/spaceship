#include "WindowsManager.h"

// LRESULT WindowsManager::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
// {
//     switch (message)
//     {
//     case WM_DESTROY:
//         {
//             SetWindowLongPtr(m_hWnd, GWLP_USERDATA, NULL);
//             m_hWnd = NULL;
//             return 0;
//         }
//     }
//     return DefWindowProc(m_hWnd, message, lParam, wParam);
// }

// https://www.codeproject.com/Articles/2556/A-Simple-Win32-Window-Wrapper-Class
// LRESULT WindowsManager::stWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
// {
//     WindowsManager* pWnd;
//     if (message == WM_NCCREATE)
//     {
//         SetWindowLong(hWnd, GWLP_USERDATA, (LONG)((LPCREATESTRUCT)lParam)->lpCreateParams);
//     }
//     pWnd = GetObjectFromWindow(hWnd);
// }

WindowsManager::WindowsManager(LPCSTR windowName, bool showCursor, int windowWidth, int windowHeight)
{
    this->windowName = windowName;
    this->showCursor = showCursor;
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    m_hWnd = NULL;
    CreateGameWindow();
}

LRESULT CALLBACK WindowsManager::WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_KEYDOWN:
        switch (wParam)
        {
    case VK_ESCAPE:
        PostQuitMessage(0);
            break;
        }
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void WindowsManager::CreateGameWindow()
{
    ZeroMemory(&wndClass, sizeof(wndClass));

    wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hInstance = GetModuleHandle(NULL);
    wndClass.lpfnWndProc = (WNDPROC)(WindowProcedure);
    wndClass.lpszClassName = windowName;
    wndClass.style = CS_HREDRAW | CS_VREDRAW;

    RegisterClass(&wndClass);
    m_hWnd = CreateWindowA(windowName, windowName, WS_OVERLAPPEDWINDOW, 0, 0, windowWidth, windowHeight, NULL, NULL,
                           GetModuleHandle(NULL), NULL);
    ShowWindow(m_hWnd, 1);
    ShowCursor(showCursor);
}

bool WindowsManager::WindowIsRunning()
{
    ZeroMemory(&msg, sizeof(msg));
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT) return false;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return true;
}

void WindowsManager::CleanUpGameWindow()
{
    if (m_hWnd)
    {
        SetWindowLong(m_hWnd, GWLP_USERDATA, 0);
    }
    UnregisterClass(wndClass.lpszClassName, GetModuleHandle(NULL));
}

HWND WindowsManager::GetHandle()
{
    return this->m_hWnd;
}
