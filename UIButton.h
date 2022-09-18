#pragma once
#include "UIObject.h"
#include "UILabel.h"
#include <d3dx9.h>

class UIButton : public UIObject
{
protected:
	HRESULT(*onClick)();
	UILabel* label;
	bool isClicked;
	LPD3DXLINE line;
	D3DXVECTOR2* vertex;
	D3DCOLOR color;

public:

	// Construtor
	UIButton(LPCSTR labelText, LPDIRECT3DDEVICE9 d3dDevice, D3DXVECTOR2 initialPosition, int width, int height, int zIndex, HRESULT(*onClick)());

	// Destructors
	~UIButton();

	// Mutators
	void SetOnClickFunction(HRESULT(*onClick)());
	void SetLabel(UILabel*);
	void SetLabel(LPCSTR);

	// Accessors
	UILabel GetLabel();
	std::string GetLabelText();

	// Game loop
	void InitUI();
	void Update(DIMOUSESTATE mouseState);
	void Render();
	void CleanUp();
};
