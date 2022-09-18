#pragma once
#include "UIFrame.h"
#include <vector>

class UIManager
{
private:
	std::vector<UIFrame> frameArr;
	int frameIndex;
	LPD3DXLINE line;
	
public:
	UIManager();
	~UIManager();
	void SortArray();
	void AddFrame(UIFrame newFrame);
	void DropFrame(UIFrame* frameRef);
	void SwitchFrame(int index);
	void NextFrame();
	void Update(DIMOUSESTATE mouseState);
	void Render(LPD3DXSPRITE spriteBrush);
	void CleanUp();
	void CleanUpFrame();
};

