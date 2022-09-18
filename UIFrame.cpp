#include "UIFrame.h"

UIFrame::UIFrame()
{
}

UIFrame::~UIFrame()
{
}

//void UIFrame::SortArray()
//{
//	std::sort(canvasArr.begin(), canvasArr.end());
//}

void UIFrame::InitUI()
{
	for (int i = 0; i < canvasArr.size(); i++) {
		UIObject* o = &canvasArr[i];
		o->InitUI();
	}
}

void UIFrame::AddCanvas(UICanvas newCanvas)
{
	canvasArr.push_back(newCanvas);
	// SortArray();
}

void UIFrame::DropCanvas(UICanvas* canvasRef)
{
	for (int i = 0; i < canvasArr.size(); i++) {
		UIObject* o = &canvasArr[i];
		if (o == canvasRef) {
			canvasArr.erase(canvasArr.begin() + i);
			break;
		}
		i++;
	}
	//SortArray();
}

void UIFrame::Update(DIMOUSESTATE mouseState)
{
	for (UICanvas o : canvasArr) {
		o.Update(mouseState);
	}
}

void UIFrame::Render()
{
	for (UICanvas o : canvasArr) {
		o.Render();
	}
}

void UIFrame::CleanUp()
{
	for (UICanvas o : canvasArr) {
		o.CleanUp();
		DropCanvas(&o);
	}
}
