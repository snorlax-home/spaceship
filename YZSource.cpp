#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>

#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

#include "AudioManager.h"
#include "FrameTimer.h"
#include "Spaceship.h"
#include "Mass.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#define WindowWidth 800
#define WindowHeight 600

//	Window handle
HWND g_hWnd = NULL;
WNDCLASS wndClass;
HRESULT hr;

// Direct Input Globals
LPDIRECTINPUT8 dInput;
LPDIRECTINPUTDEVICE8 dInputKeyboardDevice;
LPDIRECTINPUTDEVICE8 dInputMouseDevice;
BYTE diKeys[256];
DIMOUSESTATE mouseState;

// DX Globals
IDirect3DDevice9* d3dDevice = NULL;
LPD3DXSPRITE spriteBrush = NULL;

// Audio Globals
AudioManager* audioManager;
FMOD_RESULT result;
FMOD::Sound* backgroundMusic, * pointSound, * bounceSound;

// Game level global
LPDIRECT3DTEXTURE9 playertexture = NULL;
LPDIRECT3DTEXTURE9 massTexture = NULL;

// Player Number
// player 1
int player1Number = 0;

// player 2
int player2Number = 0;

// Player Keys
// player1
bool leftKeyPressed = false;
bool rightKeyPressed = false;
bool upKeyPressed = false;
bool downKeyPressed = false;

// player2
bool aKeyPressed = false;
bool dKeyPressed = false;
bool wKeyPressed = false;
bool sKeyPressed = false;

Spaceship* player1 = new Spaceship();
Spaceship* player2 = new Spaceship();
Mass* mass1 = new Mass();
Mass* mass2 = new Mass();
Mass* mass3 = new Mass();
Mass* massArray[3] = { mass1, mass2, mass3 };

float friction = 0;

void HRManager(std::string errorMessage)
{
	if (FAILED(hr))
	{
		std::cout << errorMessage << std::endl;
	}
}

void PrintLine(std::string message)
{
	std::cout << message << std::endl;
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
	wndClass.lpszClassName = "Pinball Machine";
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndClass);

	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "Pinball Machine", WS_OVERLAPPEDWINDOW, 0, 100, WindowWidth, WindowHeight, NULL, NULL, GetModuleHandle(NULL), NULL);
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

	hr = direct3D9->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_R8G8B8, TRUE, D3DMULTISAMPLE_4_SAMPLES, NULL);
	HRManager("Anti-Aliasing is not supported.");

	hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);
	HRManager("Failed to create Direct3D device!");

	hr = D3DXCreateSprite(d3dDevice, &spriteBrush);
	HRManager("Failed to create sprite brush.");

	hr = d3dDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
	HRManager("Failed to enable Multi Sample Anti Alias.");
}

void CreateDirectInput()
{
	hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);
	HRManager("Failed to create Direct Input Object.");

	hr = dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);
	HRManager("Failed to create Keyboard Device.");

	dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);

	dInputKeyboardDevice->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	hr = dInput->CreateDevice(GUID_SysMouse, &dInputMouseDevice, NULL);
	HRManager("Failed to create Mouse Device.");

	dInputMouseDevice->SetDataFormat(&c_dfDIMouse);
	dInputMouseDevice->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
}

//const int massCount = 3;
//Mass  massArray[massCount];
void InitializeLevel()
{
	srand(time(0));
	hr = D3DXCreateTextureFromFile(d3dDevice, "Assets/practical9.png", &playertexture);
	HRManager("Failed to load player texture.");

	// load mass
	hr = D3DXCreateTextureFromFile(d3dDevice, "Assets/mass.png", &massTexture);
	HRManager("Failed to load mass texture.");

	friction = 0.05;

	// player1
	player1Number = 1;
	player1->Init(1, 64, 64, 2, 2, 10, 1, 600, 300, 1.0, 0, 1, 0.1);

	// player2
	player2Number = 2;

	player2->Init(2, 64, 64, 2, 2, 10, 1, 100, 300, 1.0, 0, 1, 0.1);

	

	//for (int i = 0; i < massCount; i++)
	//{
	//	massArray[i] = Mass();
	//	massArray[i].Init(32, 32, 9, 9, WindowWidth, WindowHeight, 1, 1);

	//	//std::cout << massArray[i].GetPosition().x << std::endl;
	//	//std::cout << massArray[i].GetPosition().y << std::endl;
	//}

	// mass1
	mass1->Init(32, 32, 9, 9, WindowWidth, WindowHeight, 1, 1);

	// mass2
	mass2->Init(32, 32, 9, 9, WindowWidth, WindowHeight, 1, 1);

	// mass3
	mass3->Init(32, 32, 9, 9, WindowWidth, WindowHeight, 1, 1);

	// TODO: make this work
	// audioManager->PlaySoundtrack();
	/*audioManager->CreateStreams("Assets/Audio/space-theme.wav", backgroundMusic, true);
	audioManager->PlaySounds(backgroundMusic);*/

}

void GetInput()
{
	dInputKeyboardDevice->Acquire();

	dInputKeyboardDevice->GetDeviceState(256, diKeys);

	dInputMouseDevice->GetDeviceState(sizeof(mouseState), (LPVOID)&mouseState);
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
			PrintLine("Up Pressed!");
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
			PrintLine("Down Pressed!");
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
			PrintLine("Left Pressed!");
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
			PrintLine("Right Pressed!");
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
			PrintLine("W Pressed!");
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
			PrintLine("S Pressed!");
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
			PrintLine("A Pressed!");
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
			PrintLine("D Pressed!");
		}
	}
}

void Update(int framesToUpdate)
{
	//for (int i = 0; i < framesToUpdate; i++)
	//{
	//	player1->Update(aKeyPressed, dKeyPressed, wKeyPressed, sKeyPressed, friction, player2, massArray, 3, WindowWidth, WindowHeight, player1Number);
	//	player2->Update(leftKeyPressed, rightKeyPressed, upKeyPressed, downKeyPressed, friction, player1, massArray, 3, WindowWidth, WindowHeight, player2Number);
	//	// TODO: Ideally have mass own update to check for collision with player
	//}
	
	player1->Update(aKeyPressed, dKeyPressed, wKeyPressed, sKeyPressed, friction, player2, massArray, 3, WindowWidth, WindowHeight);
	player2->Update(leftKeyPressed, rightKeyPressed, upKeyPressed, downKeyPressed, friction, player1, massArray, 3, WindowWidth, WindowHeight);

	// player1
	aKeyPressed = false;
	dKeyPressed = false;
	wKeyPressed = false;
	sKeyPressed = false;

	// player2
	leftKeyPressed = false;
	rightKeyPressed = false;
	upKeyPressed = false;
	downKeyPressed = false;

	
}

void Render()
{
	//	Clear the back buffer.
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

	//	Begin the scene
	d3dDevice->BeginScene();

	//	To Do:
	//	Drawing.
	//	Specify alpha blend will ensure that the sprite will render the background with alpha.
	spriteBrush->Begin(D3DXSPRITE_ALPHABLEND); // enable alpha value

	//for (int i = 0; i < massCount; i++)
	//{
	//	massArray[i].Draw(spriteBrush, massTexture);
	//}

	// draw player 1
	player1->Draw(spriteBrush, playertexture);

	// draw player 2
	player2->Draw(spriteBrush, playertexture);
	

	//// draw mass 1
	//if (mass1->GetHp() > 0)
	//{
	//	mass1->Draw(spriteBrush, massTexture);
	//}
	//// draw mass 2
	//if (mass2->GetHp() > 0)
	//{
	//	mass2->Draw(spriteBrush, massTexture);
	//}

	//// draw mass 3
	//if (mass3->GetHp() > 0)
	//{
	//	mass3->Draw(spriteBrush, massTexture);
	//}

	mass1->Draw(spriteBrush, massTexture);
	mass2->Draw(spriteBrush, massTexture);
	mass3->Draw(spriteBrush, massTexture);
	

	//	End sprite drawing
	spriteBrush->End();

	//	End the scene
	d3dDevice->EndScene();

	//	Present the back buffer to screen
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void PlaySound()
{
}

bool WindowIsRunning()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
			return false;
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

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	CreateGameWindow();
	CreateDirectX();
	CreateDirectInput();

	// Initialize Managers
	FrameTimer* timer = new FrameTimer();
	timer->Init(2);

	audioManager = new AudioManager();
	audioManager->InitializeAudio();

	InitializeLevel();

	PrintLine("Game Window Created");
	while (WindowIsRunning())
	{
		GetInput();
		Update(timer->FramesToUpdate());
		Render();
		PlaySound();
	}
	PrintLine("Game Window Ended");
	CleanUpDirectInput();
	CleanUpDirectX();
	CleanUpGameWindow();

	return 0;
}