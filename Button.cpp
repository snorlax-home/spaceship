#include "Button.h"
#include "Colors.h"
#include <d3dx9.h>
#include "Utils.cpp"

void Button::SetMouseX(LONG X)
{
    this->mouseX = X;
}

void Button::SetMouseY(LONG Y)
{
    this->mouseY = Y;
}

Button::Button(std::function<void(StateMachine*)> onClick, LPCSTR buttonText, D3DXVECTOR2 position,
               D3DXVECTOR2 size, D3DCOLOR color,
               D3DCOLOR textColor, D3DCOLOR hoverColor, D3DCOLOR hoverTextColor, D3DCOLOR clickColor,
               D3DCOLOR clickTextColor, LPDIRECT3DDEVICE9 d3dDevice, StateMachine* stateMachine)
{
    this->stateMachine = stateMachine;
    this->onClick = onClick;
    this->buttonText = buttonText;
    this->position = position;
    this->size = size;
    this->color = color;
    this->textColor = textColor;
    this->hoverColor = hoverColor;
    this->hoverTextColor = hoverTextColor;
    this->clickColor = clickColor;
    this->clickTextColor = clickTextColor;
    this->isHover = false;
    this->isClick = false;
    this->mouseX = 0;
    this->mouseY = 0;
    CalcRect();
    this->label = InitLabel(d3dDevice);
    this->line = InitLine(d3dDevice);
}

void Button::CalcRect()
{
    RECT calcRect;
    calcRect.left = position.x;
    calcRect.top = position.y;
    calcRect.right = position.x + size.x;
    calcRect.bottom = position.y + size.y;
    rect = calcRect;
}

Label* Button::InitLabel(LPDIRECT3DDEVICE9 d3dDevice)
{
    this->label = nullptr;
    // Initialize label with button size and position
    // Label will be vertically and horizontally centered
    return new Label(d3dDevice, buttonText, textColor, position, size.x,
                     size.y, DT_CENTER | DT_VCENTER);
}

Line* Button::InitLine(LPDIRECT3DDEVICE9 d3dDevice)
{
    this->line = nullptr;
    // Construct vertexes for the line box
    std::vector<D3DXVECTOR2> vertex{
        D3DXVECTOR2(position.x, position.y),
        D3DXVECTOR2(position.x + size.x, position.y),
        D3DXVECTOR2(position.x + size.x, position.y + size.y),
        D3DXVECTOR2(position.x, position.y + size.y),
        D3DXVECTOR2(position.x, position.y)
    };
    D3DCOLOR renderColor;
    // Set the render color based on button state
    if (isHover)
    {
        renderColor = hoverColor;
    }
    else if (isClick)
    {
        renderColor = clickColor;
    }
    else
    {
        renderColor = color;
    }

    // Return line component
    return new Line(d3dDevice, vertex.size(), vertex, renderColor);
}

void Button::Render(LPD3DXSPRITE spriteBrush)
{
    label->Render(spriteBrush);
}

void Button::CleanUp()
{
    line->CleanUp();
}

void Button::RenderLine()
{
    line->Render();
}

void Button::GetInput(LONG X, LONG Y, DIMOUSESTATE mouseState)
{
    SetMouseX(X);
    SetMouseY(Y);
    this->mouseState = mouseState;
}

void Button::Update()
{
    // Check hover state
    if (mouseX > rect.left && mouseX < rect.right && mouseY > rect.top && mouseY < rect.bottom)
    {
        // Mouse has collision with button
        isHover = true;
    }
    else
    {
        isHover = false;
    }
    
    if (mouseState.rgbButtons[0] & 0x80)
    {
        // Left mouse button down event
        if (isHover)
        {
            // Mouse has click inside button
            isClick = true;
            // Trigger onClick function
            onClick(stateMachine);
        }
    }
    else
    {
        isClick = false;
    }


    // Update label
    if (isClick)
    {
        label->SetColor(clickTextColor);
        line->SetColor(clickColor);
    }
    else if (isHover)
    {
        label->SetColor(hoverTextColor);
        line->SetColor(hoverTextColor);
    }
    else
    {
        label->SetColor(textColor);
        line->SetColor(color);
    }
}
