#pragma once
#include "UIObject.h"
#include <d3dx9.h>
#include <vector>

class UICanvas : public UIObject {
private:
	std::vector<UIObject*> children;
	int zIndex;

public:
	UICanvas();
	~UICanvas();
	// void SortArray();
	void AddChild(UIObject* newObject);
	void DropChild(UIObject* objectRefs);
	void InitUI();
	void Update(DIMOUSESTATE mouseState);
	void Render();
	void CleanUp();
};