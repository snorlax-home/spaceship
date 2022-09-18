#pragma once
#include "UICanvas.h"
#include <vector>

class UIFrame {
private:
	std::vector<UICanvas> canvasArr;

public:
	UIFrame();
	~UIFrame();
	// void SortArray();
	void InitUI();
	void AddCanvas(UICanvas newCanvas);
	void DropCanvas(UICanvas* canvasRef);
	void Update(DIMOUSESTATE mouseState);
	void Render();
	void CleanUp();
};