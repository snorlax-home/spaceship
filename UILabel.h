#pragma once
#include "UIObject.h"
#include <string>

class UILabel : public UIObject {
protected:
	LPCSTR displayText;
	LPD3DXFONT font;

public:
	// Constructor
	UILabel(LPCSTR displayText, LPDIRECT3DDEVICE9 d3dDevice, D3DXVECTOR2 initialPosition, int width, int height, int zIndex);
	
	// Mutators
	void SetText(LPCSTR displayText);
	void SetFont(LPD3DXFONT font);
	
	// Accessors
	LPCSTR GetText();
	LPD3DXFONT GetFont();
	
	// Game loop
	void InitUI();
	void Update(DIMOUSESTATE mouseState);
	void Render();
	void CleanUp();
	
};