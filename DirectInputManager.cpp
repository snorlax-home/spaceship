#include "DirectInputManager.h"
#include "Utils.cpp"

DirectInputManager::DirectInputManager(WindowsManager* windowManager)
{
    // Get window manager for window handle
    this->windowManager = windowManager;

    // Initialize direct input
    Init();
}

void HRHandler(HRESULT hr, const char* currentProcess)
{
    if (FAILED(hr))
    {
        std::cout << "Failed : " << currentProcess << std::endl;
    }
    else
    {
        std::cout << "Success : " << currentProcess << std::endl;
    }
}


void DirectInputManager::Init()
{
    HRESULT hr;

    // Create direct input interface
    hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);
    HRHandler(hr, "Create direct input interface");

    // Create keyboard device, set data format and cooperative level
    hr = dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);
    HRHandler(hr, "Create direct input keyboard device");
    dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
    dInputKeyboardDevice->SetCooperativeLevel(windowManager->GetHandle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

    // Create mouse device, set data format and cooperative level
    hr = dInput->CreateDevice(GUID_SysMouse, &dInputMouseDevice, NULL);
    HRHandler(hr, "Create direct input mouse device");
    dInputMouseDevice->SetDataFormat(&c_dfDIMouse);
    dInputMouseDevice->SetCooperativeLevel(windowManager->GetHandle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
}

void DirectInputManager::GetInput()
{
    // Acquire keyboard and get current state of keyboard then save into BYTE array
    dInputKeyboardDevice->Acquire();
    dInputKeyboardDevice->GetDeviceState(256, diKeys);

    // Acquire mouse device and get current state of mouse device then save into mouse state
    dInputMouseDevice->Acquire();
    dInputMouseDevice->GetDeviceState(sizeof(mouseState), (LPVOID)&mouseState);
}

void DirectInputManager::CleanUp()
{
    // Clean up process
    // Unacquire and release keyboard device
    dInputKeyboardDevice->Unacquire();
    dInputKeyboardDevice->Release();
    dInputKeyboardDevice = NULL;

    // Unacquire and release mouse device
    dInputMouseDevice->Unacquire();
    dInputMouseDevice->Release();
    dInputMouseDevice = NULL;

    // Release direct input interface
    dInput->Release();
    dInput = NULL;
}

DIMOUSESTATE DirectInputManager::GetMouseState()
{
    return mouseState;
}

BYTE* DirectInputManager::GetKeyState()
{
    return diKeys;
}
