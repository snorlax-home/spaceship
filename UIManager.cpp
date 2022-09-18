#include "UIManager.h"

UIManager::UIManager()
{
	this->frameIndex = -1;
}

UIManager::~UIManager()
{
}

//void UIManager::SortArray()
//{
//	std::sort(frameArr.begin(), frameArr.end());
//}

void UIManager::AddFrame(UIFrame newFrame)
{
	frameArr.push_back(newFrame);
	frameIndex++;
	// SortArray();
}

void UIManager::DropFrame(UIFrame* frameRef)
{
	int i = 0;
	for (UIFrame o : frameArr) {
		if (&o == frameRef) {
			frameArr.erase(frameArr.begin() + i);
			break;
		}
	}
	// SortArray();
}

void UIManager::SwitchFrame(int index)
{
	this->frameIndex = index;
}

void UIManager::NextFrame()
{
	if (frameIndex < (int)frameArr.size() - 1) {
		frameIndex++;
	}
}

void UIManager::Update(DIMOUSESTATE mouseState)
{
	frameArr[frameIndex].Update(mouseState);
}

void UIManager::Render(LPD3DXSPRITE spriteBrush)
{
	frameArr[frameIndex].Render(spriteBrush);
}

void UIManager::CleanUp()
{
	for (UIFrame o : frameArr) {
		o.CleanUp();
		DropFrame(&o);
	}
}

void UIManager::CleanUpFrame() {
	frameArr[frameIndex].CleanUp();
}

