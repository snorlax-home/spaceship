#pragma once

#include <dinput.h>

#include "WindowsManager.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

/**
 * \brief Manager class for direct input api
 * This class will initialize direct input and provide access to the keyboard and mouse
 * This class will get the input for both keyboard and mouse device.
 */
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
    /**
     * \brief Default constructor
     * \param windowManager WindowManager to get the window handle
     */
    DirectInputManager(WindowsManager* windowManager);

    /**
     * \brief Initialize direct input interface and devices
     */
    void Init();
    /**
     * \brief Get the mouse state
     * \return Return the state of mouse
     */
    DIMOUSESTATE GetMouseState();
    /**
     * \brief Get the keyboard data
     * \return Return a byte array of keyboard data
     */
    BYTE* GetKeyState();
    /**
     * \brief Get input from both keyboard and mouse
     */
    void GetInput();
    /**
     * \brief Clean Up the direct input interface and devices
     */
    void CleanUp();
};
