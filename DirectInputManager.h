#pragma once

#include <dinput.h>

#include "WindowsManager.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

class DirectInputManager
{
private:
    LPDIRECTINPUT8 dInput;
    LPDIRECTINPUTDEVICE8 dInputKeyboardDevice;
    LPDIRECTINPUTDEVICE8 dInputMouseDevice;
    BYTE diKeys[256];
    DIMOUSESTATE mouseState;
    WindowsManager* windowManager;
public:
    DirectInputManager(WindowsManager* windowManager);
    void Init();

    DIMOUSESTATE GetMouseState();
    BYTE* GetKeyState();
    
    void GetInput();
    void CleanUp();
};
