#pragma once
#include <d3dx9.h>
#include <dinput.h>
#include <functional>

#include "StateMachine.h"
#include "Label.h"
#include "Line.h"

/**
 * \brief UI Component Button
 *
 * This UI button is a combination of a label and a box created by line
 */

class Button
{
private:
    bool isHover;
    bool isClick;
    std::function<void(StateMachine*)> onClick;
    LPCSTR buttonText;
    D3DXVECTOR2 position;
    D3DXVECTOR2 size;
    RECT rect;
    D3DCOLOR color;
    D3DCOLOR textColor;
    D3DCOLOR hoverColor;
    D3DCOLOR hoverTextColor;
    D3DCOLOR clickColor;
    D3DCOLOR clickTextColor;
    Label* label;
    Line* line;
    StateMachine* stateMachine;
    LONG mouseX;
    LONG mouseY;
    DIMOUSESTATE mouseState;
    void SetMouseX(LONG X);
    void SetMouseY(LONG Y);
public:
    /**
     * \brief Button Default Constructor
     *
     * Default constructor for Button class that takes below parameters
     * 
     * \param onClick Function to be called when the button is clicked, it receives a pointer to the state machine 
     * \param buttonText Label text of the button
     * \param position Position of button on screen
     * \param size Dimension of button
     * \param color Default color of line box
     * \param textColor Default color of text
     * \param hoverColor Color of line box when mouse is hovering over it
     * \param hoverTextColor Color of text when mouse is hovering over it
     * \param clickColor Color of line box when mouse is clicking on it
     * \param clickTextColor Color of text when mouse is clicking on it
     * \param d3dDevice D3D Device for label and line creation
     * \param stateMachine State machine reference to manipulate the game state
     */
    Button(std::function<void(StateMachine*)> onClick, LPCSTR buttonText, D3DXVECTOR2 position, D3DXVECTOR2 size,
           D3DCOLOR color, D3DCOLOR textColor, D3DCOLOR hoverColor, D3DCOLOR hoverTextColor, D3DCOLOR clickColor,
           D3DCOLOR clickTextColor, LPDIRECT3DDEVICE9 d3dDevice, StateMachine* stateMachine);
    /**
     * \brief Calculate Position Rectangle
     *
     * Function to recalculate the position rectangle of the button
     */
    void CalcRect();
    /**
     * \brief Initialize Label of Button
     * \param d3dDevice D3D Device for label creation
     * \return Return the generated Label component
     */
    Label* InitLabel(LPDIRECT3DDEVICE9 d3dDevice);
    /**
     * \brief Initialize Line Box of Button
     * \param d3dDevice D3D Device for line creation
     * \return Return the generated Line component
     */
    Line* InitLine(LPDIRECT3DDEVICE9 d3dDevice);
    /**
     * \brief Function to render the line box
     */
    void RenderLine();
    /**
     * \brief Get Input from system
     * \param mouseX Position of cursor on X axis
     * \param mouseY Position of cursor on Y axis
     * \param mouseState Mouse State to keep track on mouse buttons
     */
    void GetInput(LONG mouseX, LONG mouseY, DIMOUSESTATE mouseState);
    /**
     * \brief Update the button state
     *
     *  Check whether there is hover and click event on button.
     *  Update the label and line box color accordingly
     */
    void Update();
    /**
     * \brief Render the button 
     * \param spriteBrush Sprite Brush to render the label
     */
    void Render(LPD3DXSPRITE spriteBrush);
    /**
     * \brief Clean up Button component
     *
     * Trigger the clean up function of label 
     */
    void CleanUp();
};
