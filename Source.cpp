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
// #include "MainMenu.cpp"
//#include "UIManager.h"
#include "Button.h"
#include "Label.h";
#include "Utils.cpp";
#include "colors.h"
#include "GameLevelManager.h"
#include "GameOver.h"
#include "Line.h"
#include "MainMenu.h"
#include "SpaceshipGameLevel.h"

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
LONG mouseX, mouseY;

//DX Globals
IDirect3DDevice9* d3dDevice = NULL;
LPD3DXSPRITE spriteBrush = NULL;

// Global managers
AudioManager* audioManager;
FrameTimer* timer;

// Game Levels
std::vector<GameLevel*> gameLevels;
GameLevelManager* gameLevelManager;

// Mouse cursor
LONG currentXpos = 0;
LONG currentYpos = 0;
LPDIRECT3DTEXTURE9 cursorTexture = NULL;
D3DXVECTOR2 cursorScaling;
D3DXVECTOR2 cursorSpriteCentre;
float cursorRotation;
RECT cursorSpriteRect;
RECT mouseColRect;
D3DXVECTOR2 cursorPosition;

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
    g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "Pinball Machine", WS_OVERLAPPEDWINDOW, 0, 100, WindowWidth,
                            WindowHeight, NULL, NULL, GetModuleHandle(NULL), NULL);
    ShowWindow(g_hWnd, 1);
    ShowCursor(0);
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

void Init()
{
    timer = new FrameTimer();
    timer->Init(60);
    audioManager = new AudioManager();
    audioManager->InitializeAudio();
    gameLevelManager = new GameLevelManager();

    MainMenu* mainMenu = new MainMenu(
        audioManager, d3dDevice, gameLevelManager
    );
    SpaceshipGameLevel* spaceshipGameLevel = new SpaceshipGameLevel(
        audioManager, d3dDevice, gameLevelManager, WindowWidth, WindowHeight
    );
    GameOver* gameOver = new GameOver(
        audioManager, d3dDevice, gameLevelManager);
    gameLevels.push_back(mainMenu);
    gameLevels.push_back(spaceshipGameLevel);
    gameLevels.push_back(gameOver);

    D3DXCreateTextureFromFile(d3dDevice, "Assets/cursor.png", &cursorTexture);

    cursorSpriteRect.left = 0;
    cursorSpriteRect.top = 0;
    cursorSpriteRect.right = 64;
    cursorSpriteRect.bottom = 64;

    cursorPosition.x = WindowHeight / 2;
    cursorPosition.y = WindowWidth / 2;

    cursorScaling = D3DXVECTOR2(1.0f, 1.0f);
    cursorSpriteCentre = D3DXVECTOR2(32, 32);
    cursorRotation = 0.0f;
}

void Update(int framesToUpdate)
{
    GetInput();
    cursorPosition.x += mouseState.lX;
    cursorPosition.y += mouseState.lY;
    mouseX = cursorPosition.x;
    mouseY = cursorPosition.y;
    gameLevels[gameLevelManager->GetCurrentLevel()]->GetInput(diKeys, mouseState);
    gameLevels[gameLevelManager->GetCurrentLevel()]->Update(diKeys, mouseState, mouseX, mouseY, framesToUpdate);
}

void Render()
{
    d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    D3DXMATRIX mat;
    d3dDevice->BeginScene();
    spriteBrush->Begin(D3DXSPRITE_ALPHABLEND);
    gameLevels[gameLevelManager->GetCurrentLevel()]->Render(spriteBrush);

    // D3DXMatrixTransformation2D(&mat, NULL, 0.0, &cursorScaling, &cursorSpriteCentre, cursorRotation, &cursorPosition);
    // spriteBrush->SetTransform(&mat);
    spriteBrush->Draw(cursorTexture, &cursorSpriteRect, NULL, new D3DXVECTOR3(cursorPosition.x, cursorPosition.y, 0),
                      D3DCOLOR_XRGB(255, 255, 255));
    spriteBrush->SetTransform(nullptr);

    spriteBrush->End();
    gameLevels[gameLevelManager->GetCurrentLevel()]->RenderLine();
    d3dDevice->EndScene();
    d3dDevice->Present(NULL, NULL, NULL, NULL);
}

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    CreateGameWindow();
    CreateDirectX();
    CreateDirectInput();

    Init();
    for (int i = 0; i < gameLevels.size(); i++)
    {
        gameLevels[i]->InitLevel();
    }
    if (FAILED(hr))
    {
        cout << "Failed to create sprite brush." << endl;
    }


    PrintLine("Game Window Created");
    while (WindowIsRunning())
    {
        if (gameLevels.empty() || gameLevelManager->GetCurrentLevel() >= gameLevels.size())
        {
            break;
        }

        Update(timer->FramesToUpdate());
        Render();
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
