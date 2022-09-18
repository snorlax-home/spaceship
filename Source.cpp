#define WIN32_LEAN_AND_MEAN
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <iostream>
#include <vector>
#include <Windows.h>

#include "AudioManager.h"
#include "FrameTimer.h"
#include "GameLevel.h"
#include "Utils.cpp";

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#define WindowWidth 800
#define WindowHeight 600
//	Window handle
HWND g_hWnd = nullptr;
WNDCLASS wndClass;
HRESULT hr;

// Direct Input Globals
LPDIRECTINPUT8 dInput;
LPDIRECTINPUTDEVICE8 dInputKeyboardDevice;
LPDIRECTINPUTDEVICE8 dInputMouseDevice;
BYTE diKeys[256];
DIMOUSESTATE mouseState;

//DX Globals
IDirect3DDevice9* d3dDevice = NULL;
LPD3DXSPRITE spriteBrush = NULL;

// Global managers
AudioManager* audioManager;
//UIManager* uiManager;
std::vector<GameLevel*> gameLevels;
int currentLevel = 0;

void HRManager(std::string errorMessage)
{
    if (FAILED(hr))
    {
        std::cout << "FAILED : " << errorMessage << std::endl;
    }
    else if (hr == S_OK)
    {
        std::cout << "SUCCESS: " << errorMessage << std::endl;
    }
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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

void CreateGameWindow()
{
    ZeroMemory(&wndClass, sizeof(wndClass));

    wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hInstance = GetModuleHandle(NULL);
    wndClass.lpfnWndProc = WindowProcedure;
    wndClass.lpszClassName = "Spaceship";
    wndClass.style = CS_HREDRAW | CS_VREDRAW;

    RegisterClass(&wndClass);

    g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "Spaceship", WS_OVERLAPPEDWINDOW, 0, 100, WindowWidth,
                            WindowHeight, NULL, NULL, GetModuleHandle(NULL), NULL);
    ShowWindow(g_hWnd, 1);
    ShowCursor(1);
}

void CreateDirectX()
{
    IDirect3D9* direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);

    D3DPRESENT_PARAMETERS d3dPP;
    ZeroMemory(&d3dPP, sizeof(d3dPP));

    d3dPP.Windowed = true;
    d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dPP.BackBufferCount = 1;
    d3dPP.MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;
    d3dPP.BackBufferWidth = WindowWidth;
    d3dPP.BackBufferHeight = WindowHeight;
    d3dPP.hDeviceWindow = g_hWnd;

    //hr = direct3D9->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_R8G8B8, TRUE, D3DMULTISAMPLE_4_SAMPLES, NULL);
    //HRManager("Anti-Aliasing is not supported.");


    hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                 &d3dPP, &d3dDevice);
    HRManager("Create Direct3D9 device.");

    spriteBrush = nullptr;
    hr = D3DXCreateSprite(d3dDevice, &spriteBrush);
    HRManager("Create sprite brush.");

}

void CreateDirectInput()
{
    hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);
    HRManager("Create Direct Input Object.");


    hr = dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);
    HRManager("Create Keyboard Device.");

    dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);

    dInputKeyboardDevice->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

    hr = dInput->CreateDevice(GUID_SysMouse, &dInputMouseDevice, NULL);
    HRManager("Create Mouse Device.");

    dInputMouseDevice->SetDataFormat(&c_dfDIMouse);
    dInputMouseDevice->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
}

void GetInput()
{
    dInputKeyboardDevice->Acquire();

    dInputKeyboardDevice->GetDeviceState(256, diKeys);

    dInputMouseDevice->GetDeviceState(sizeof(mouseState), (LPVOID)&mouseState);
    dInputMouseDevice->Acquire();
}

bool WindowIsRunning()
{
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT) return false;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return true;
}

void CleanUpDirectX()
{
    spriteBrush->Release();
    spriteBrush = NULL;

    d3dDevice->Release();
    d3dDevice = NULL;
}

void CleanUpDirectInput()
{
    dInputKeyboardDevice->Unacquire();
    dInputKeyboardDevice->Release();
    dInputKeyboardDevice = NULL;

    dInput->Release();
    dInput = NULL;
}

void CleanUpGameWindow()
{
    UnregisterClass(wndClass.lpszClassName, GetModuleHandle(NULL));
}


void Update(int framesToUpdate)
{
    for (int i = 0; i < framesToUpdate; i++)
    {
        // gameLevels[currentLevel]->Update();
    }
}

void Render()
{
    d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    d3dDevice->BeginScene();
    spriteBrush->Begin(D3DXSPRITE_ALPHABLEND);
    // Render sprites
    spriteBrush->End();
    // Render lines
    d3dDevice->EndScene();
    d3dDevice->Present(NULL, NULL, NULL, NULL);
}

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    CreateGameWindow();
    CreateDirectX();
    CreateDirectInput();

    // Initialize Managers
    FrameTimer* timer = new FrameTimer();
    timer->Init(60);

    audioManager = new AudioManager();
    audioManager->InitializeAudio();
    if (FAILED(hr))
    {
        cout << "Failed to create sprite brush." << endl;
    }
    PrintLine("Game Window Created");
    while (WindowIsRunning())
    {
        Update(timer->FramesToUpdate());
        Render();
        // if (gameLevels.empty())
        // {
        //     break;
        // }
        // gameLevels[currentLevel]->Update(*diKeys, mouseState);
        // gameLevels[currentLevel]->Render(spriteBrush);
    }
    PrintLine("Game Window Ended");
    while (!gameLevels.empty())
    {
        gameLevels[0]->CleanUp();
        gameLevels.erase(gameLevels.begin());
    }

    CleanUpDirectInput();
    CleanUpDirectX();
    CleanUpGameWindow();

    return 0;
}
