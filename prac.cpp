//	Ask the compiler to include minimal header files for our program.
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include <d3d9.h>   //	include the Direct3D 9 library
#include <d3dx9.h>  //	include the D3DX9 library
#include <dinput.h> //	include the Direct Input library.
#include "FrameTimer.h"
#include "AudioManager.h"
#include "Spaceship.h"
#include "Mass.h"
//--------------------------------------------------------------------
using namespace std;

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#define WindowWidth 800
#define WindowHeight 600

HWND g_hWnd = NULL; //	Window handle
WNDCLASS wndClass;  //	Window's structure

// DX globals
IDirect3DDevice9 *d3dDevice;
LPD3DXSPRITE spriteBrush = NULL; // sprite is the thing draw in the screen (spriteBrush)
LPD3DXFONT font = NULL;
LPD3DXLINE line = NULL;
LPDIRECTINPUT8 dInput;                     //	Direct Input object.
LPDIRECTINPUTDEVICE8 dInputKeyboardDevice; //	Direct Input keyboard device.
LPDIRECTINPUTDEVICE8 dInputMouseDevice;    //	Direct Input keyboard device.
BYTE diKeys[256];                          //	Key input buffer
DIMOUSESTATE mouseStates;                  // mouse input buffer

// Game level global
LPDIRECT3DTEXTURE9 playertexture = NULL;
LPDIRECT3DTEXTURE9 massTexture = NULL;
AudioManager *audioManager;

// player 1
int player1Number = 0;

// player 2
int player2Number = 0;

// mouse texture
LPDIRECT3DTEXTURE9 mousetexture = NULL;
RECT mouseRect;
RECT mouseColRect;
D3DXVECTOR3 mouseposition;

RECT textRect;

HRESULT hr;

bool leftKeyPressed = false;
bool rightKeyPressed = false;
bool upKeyPressed = false;
bool downKeyPressed = false;

bool aKeyPressed = false;
bool dKeyPressed = false;
bool wKeyPressed = false;
bool sKeyPressed = false;

FrameTimer *timer = new FrameTimer();
Spaceship *player1 = new Spaceship();
Spaceship *player2 = new Spaceship();
Mass *mass1 = new Mass();
Mass *mass2 = new Mass();

float friction = 0;

//--------------------------------------------------------------------

//	Window Procedure, for event handling
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        //	The message is post when we destroy the window.

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            break;
        }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
        return 0;
    }
}

void CreateMyWindow()
{
    //	Set all members in wndClass to 0.
    ZeroMemory(&wndClass, sizeof(wndClass));

    //	Filling wndClass. You are to refer to MSDN for each of the members details.
    //	These are the fundamental structure members to be specify, in order to create your window.
    wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hInstance = GetModuleHandle(NULL);
    wndClass.lpfnWndProc = WindowProcedure;
    wndClass.lpszClassName = "My Window";
    wndClass.style = CS_HREDRAW | CS_VREDRAW;

    //	Register the window.
    RegisterClass(&wndClass);

    //	You are to refer to MSDN for each of the parameters details.
    g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "My Window's Name", WS_OVERLAPPEDWINDOW, 0, 100, WindowWidth, WindowHeight, NULL, NULL, GetModuleHandle(NULL), NULL);
    ShowWindow(g_hWnd, 1);
}

void CreateMyDX()
{
    //	Define Direct3D 9.
    IDirect3D9 *direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);

    //	Define how the screen presents.
    D3DPRESENT_PARAMETERS d3dPP;
    ZeroMemory(&d3dPP, sizeof(d3dPP));

    //	Refer to Direct3D 9 documentation for the meaning of the members.
    d3dPP.Windowed = true;
    d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dPP.BackBufferCount = 1;
    d3dPP.BackBufferWidth = WindowWidth;
    d3dPP.BackBufferHeight = WindowHeight;
    d3dPP.hDeviceWindow = g_hWnd;

    //	Create a Direct3D 9 device.
    hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL /*D3DDEVTYPE_REF*/, g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);
    //	To Do: Cout out the message to indicate the failure.
    if (FAILED(hr))
        cout << "Create DirectX Failed" << endl;

    //	Create sprite. Study the documentation.
    hr = D3DXCreateSprite(d3dDevice, &spriteBrush);

    if (FAILED(hr))
    {
        cout << "sprite fail" << endl;
    }

    // Create text.
    hr = D3DXCreateFont(d3dDevice, 25, 0, 0, 1, false,
                        DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
                        DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);

    // Create Line
    hr = D3DXCreateLine(d3dDevice, &line);
    // return 0;
}

void CreateMyDInput()
{
    //	Create the Direct Input object.
    hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void **)&dInput, NULL);

    if (FAILED(hr))
    {
        cout << "input object fail" << endl;
    }

    //	Create the keyboard device.
    hr = dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);

    if (FAILED(hr))
    {
        cout << "keyboard fail" << endl;
    }

    //	Set the input data format.
    hr = dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);

    if (FAILED(hr))
    {
        cout << "keyboard input data fail" << endl;
    }

    //	Set the cooperative level.
    //	To Do:
    //	Try with different combination.
    hr = dInputKeyboardDevice->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

    if (FAILED(hr))
    {
        cout << "cooperative level fail" << endl;
    }

    // mouse//
    //	Create the mouse device.
    hr = dInput->CreateDevice(GUID_SysMouse, &dInputMouseDevice, NULL);

    if (FAILED(hr))
    {
        cout << "mouse fail" << endl;
    }

    //	Set the input data format.
    hr = dInputMouseDevice->SetDataFormat(&c_dfDIMouse);

    if (FAILED(hr))
    {
        cout << "mouse input data fail" << endl;
    }

    //	Set the cooperative level.
    //	To Do:
    //	Try with different combination.
    hr = dInputKeyboardDevice->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    mouseposition.x = WindowWidth / 2;
    mouseposition.y = WindowHeight / 2;

    if (FAILED(hr))
    {
        cout << "cooperative level fail" << endl;
    }
}

void InitializeLevel()
{
    srand(time(0));

    //	Create texture. Study the documentation.

    // TODO: How do we want to deal with playerTexture
    hr = D3DXCreateTextureFromFile(d3dDevice, "Assets/practical9.png", &playertexture);

    if (FAILED(hr))
    {
        cout << "texture fail" << endl;
    }

    // load mass
    hr = D3DXCreateTextureFromFile(d3dDevice, "Assets/mass.png", &massTexture);

    if (FAILED(hr))
    {
        cout << "texture fail" << endl;
    }

    // mouse
    mouseRect.left = 0;
    mouseRect.top = 0;
    mouseRect.right = 32;
    mouseRect.bottom = 32;
    // mouse collision
    mouseColRect.left = 0;
    mouseColRect.top = 0;
    mouseColRect.right = 32;
    mouseColRect.bottom = 32;

    friction = 0.05;

    // player1
    player1Number = 1;
    // TODO: Player Texture hw
    player1->Init(64, 64, 2, 2, 10, 1, 0, 0, 600, 300, 1.0, 0, 1, 0.1);

    // player2
    player2Number = 2;

    player2->Init(64, 64, 2, 2, 10, 1, 32, 0, 100, 300, 1.0, 0, 1, 0.1);

    // mass1
    mass1->Init(32, 32, 9, 9, 0, 0, WindowWidth, WindowHeight, 1, 1);

    // mass2
    mass2->Init(32, 32, 9, 9, 0, 0, WindowWidth, WindowHeight, 1, 1);

    //audioManager->PlaySoundtrack();
}

void GetInput()
{
    //	Get immediate Keyboard Data.
    dInputKeyboardDevice->GetDeviceState(256, diKeys);
    //	Acquire the device.
    dInputKeyboardDevice->Acquire();
    dInputMouseDevice->Acquire();

    // TODO: Set upKeyPressed to false should not be done here
    //  player1 movement
    if (diKeys[DIK_UP] & 0x80)
    {
        if (player1->GetPosition().y == 0)
        {
            upKeyPressed = false;
        }
        else
        {
            upKeyPressed = true;
            cout << "Up Pressed!" << endl;
        }
    }

    if (diKeys[DIK_DOWN] & 0x80)
    {
        if (player1->GetPosition().y > WindowHeight - player1->GetSpriteHeight())
        {
            downKeyPressed = false;
        }
        else
        {
            downKeyPressed = true;
            cout << "Down Pressed!" << endl;
        }
    }

    if (diKeys[DIK_LEFT] & 0x80)
    {
        if (player1->GetPosition().x == 0)
        {
            leftKeyPressed = false;
        }
        else
        {
            leftKeyPressed = true;
            cout << "Left Pressed!" << endl;
        }
    }

    if (diKeys[DIK_RIGHT] & 0x80)
    {
        if (player1->GetPosition().x > WindowWidth - player1->GetSpriteWidth())
        {
            rightKeyPressed = false;
        }
        else
        {
            rightKeyPressed = true;
            cout << "Right Pressed!" << endl;
        }
    }

    // player2 movement
    if (diKeys[DIK_W] & 0x80)
    {
        if (player2->GetPosition().y == 0)
        {
            wKeyPressed = false;
        }
        else
        {
            wKeyPressed = true;
            cout << "W Pressed!" << endl;
        }
    }

    if (diKeys[DIK_S] & 0x80)
    {
        if (player2->GetPosition().y > WindowHeight - player2->GetSpriteHeight())
        {
            sKeyPressed = false;
        }
        else
        {
            sKeyPressed = true;
            cout << "S Pressed!" << endl;
        }
    }

    if (diKeys[DIK_A] & 0x80)
    {
        if (player2->GetPosition().x == 0)
        {
            aKeyPressed = false;
        }
        else
        {
            aKeyPressed = true;
            cout << "A Pressed!" << endl;
        }
    }

    if (diKeys[DIK_D] & 0x80)
    {
        if (player2->GetPosition().x > WindowWidth - player2->GetSpriteWidth())
        {
            dKeyPressed = false;
        }
        else
        {
            dKeyPressed = true;
            cout << "D Pressed!" << endl;
        }
    }

    dInputMouseDevice->GetDeviceState(sizeof(mouseStates), &mouseStates);
}

void Update(int framesToUpdate)
{
    for (int i = 0; i < framesToUpdate; i++)
    {
        // player1

        player1->Move(leftKeyPressed, rightKeyPressed, upKeyPressed, downKeyPressed, friction);

        player1->CollisionSpaceship(player2);
        player1->CollisionMass(mass1);
        player1->CollisionMass(mass2);

        // player2
        player2->Move(aKeyPressed, dKeyPressed, wKeyPressed, sKeyPressed, friction);

        player2->CollisionSpaceship(player1);
        player2->CollisionMass(mass1);
        player2->CollisionMass(mass2);

        player1->WindowBounce(WindowWidth, WindowHeight);
        player2->WindowBounce(WindowWidth, WindowHeight);

        // p1 and p2 animation
        // TODO: implement spriteFPS to make sure it does not flash too much
        player1->NextFrame(player1Number);
        player2->NextFrame(player2Number);
    }

    // player1
    leftKeyPressed = false;
    rightKeyPressed = false;
    upKeyPressed = false;
    downKeyPressed = false;

    // player2
    aKeyPressed = false;
    dKeyPressed = false;
    wKeyPressed = false;
    sKeyPressed = false;
}

void Render()
{
    //	Clear the back buffer.
    d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    //	Begin the scene
    d3dDevice->BeginScene();

    //	To Do:
    //	Drawing.
    //	Specify alpha blend will ensure that the sprite will render the background with alpha.
    spriteBrush->Begin(D3DXSPRITE_ALPHABLEND); // enable alpha value

    D3DXMATRIX mat;

    // draw player 1
    D3DXMatrixTransformation2D(&mat, NULL, 0.0, player1->GetScalingAddress(), player1->GetSpriteCenterAddress(), player1->GetDirection(), player1->GetPositionAddress());
    spriteBrush->SetTransform(&mat);
    HRESULT hr = spriteBrush->Draw(playertexture, player1->GetDisplayRectAddress(), NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

    // draw player 2
    D3DXMatrixTransformation2D(&mat, NULL, 0.0, player2->GetScalingAddress(), player2->GetSpriteCenterAddress(), player2->GetDirection(), player2->GetPositionAddress());
    spriteBrush->SetTransform(&mat);
    spriteBrush->Draw(playertexture, player2->GetDisplayRectAddress(), NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

    // draw mass 1
    if (mass1->GetHp() > 0)
    {
        D3DXMatrixTransformation2D(&mat, NULL, 0.5f, mass1->GetScalingAddress(), mass1->GetSpriteCenterAddress(), 0, mass1->GetPositionAddress());
        spriteBrush->SetTransform(&mat);
        spriteBrush->Draw(massTexture, mass1->GetDisplayRectAddress(), NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
    }
    // draw mass 2
    if (mass2->GetHp() > 0)
    {
        D3DXMatrixTransformation2D(&mat, NULL, 0.5f, mass2->GetScalingAddress(), mass2->GetSpriteCenterAddress(), 0, mass2->GetPositionAddress());
        spriteBrush->SetTransform(&mat);
        spriteBrush->Draw(massTexture, mass2->GetDisplayRectAddress(), NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
    }
    //	End sprite drawing
    spriteBrush->End();

    //	End the scene
    d3dDevice->EndScene();

    //	Present the back buffer to screen
    d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void PlaySound() {
	//audioManager->UpdateSound();
	player1->SpaceshipPlaySound(audioManager);
	player2->SpaceshipPlaySound(audioManager);
}

bool WindowIsRunning()
{
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        //	Receive a quit message
        if (msg.message == WM_QUIT)
            return false;
        //	Translate the message
        TranslateMessage(&msg);
        //	Send message to your window procedure
        DispatchMessage(&msg);
    }
    return true;
}

void CleanupMyLevel()
{
    spriteBrush->Release();
    spriteBrush = NULL;

    playertexture->Release();
    playertexture = NULL;

    // mousetexture->Release();
    // mousetexture = NULL;
}

void CleanupMyWindow()
{
    //	Free up the memory.
    UnregisterClass(wndClass.lpszClassName, GetModuleHandle(NULL));
}

void CleanupMyDX()
{
    //	Release the device when exiting.
    d3dDevice->Release();
    //	Reset pointer to NULL, a good practice.
    d3dDevice = NULL;

    font->Release();
    font = NULL;

    line->Release();
    line = NULL;
}

void CleanupMyDInput()
{
    //	Release keyboard device.
    dInputKeyboardDevice->Acquire();
    dInputKeyboardDevice->Release();
    dInputKeyboardDevice = NULL;

    //	Release DirectInput.
    dInput->Release();
    dInput = NULL;
}

//	use WinMain if you don't want the console
int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    CreateMyWindow();
    CreateMyDX();
    CreateMyDInput();

    audioManager = new AudioManager();

    //audioManager->InitalizeAudio();
    //audioManager->LoadSounds();
    //audioManager->PlaySound1();
    //audioManager->PlaySoundtrack();

    timer->Init(60);

    InitializeLevel();

    while (WindowIsRunning())
    {
        GetInput();
        Update(timer->FramesToUpdate());
        Render();
  		PlaySound();
    }

    CleanupMyLevel();
    CleanupMyDInput();
    CleanupMyDX();
    CleanupMyWindow();

    return 0;
}