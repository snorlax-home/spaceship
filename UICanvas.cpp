#include "UICanvas.h"

UICanvas::UICanvas()
{
	zIndex = 0;
}

UICanvas::~UICanvas()
{
}

//void UICanvas::SortArray()
//{
//	std::sort(children.begin(), children.end());
//}

void UICanvas::AddChild(UIObject* newObject)
{
	children.push_back(newObject);
	//SortArray();
}

void UICanvas::DropChild(UIObject* objectRef)
{
	for (int i = 0; i < children.size(); i++) {
		UIObject* o = children[i];
		if (o == objectRef) {
			children.erase(children.begin() + i);
			break;
		}
		i++;
	}
	//SortArray();
}

void UICanvas::InitUI()
{
	for (int i = 0; i < children.size(); i++) {
		UIObject* o = children[i];
		o->InitUI();
	}
}

void UICanvas::Update(DIMOUSESTATE mouseState) {
	this->mouseState = mouseState;
	for (int i = 0; i < children.size(); i++) {
		UIObject* o = children[i];
		o->Update(mouseState);
	}
}

void UICanvas::Render()
{
	for (int i = 0; i < children.size(); i++) {
		UIObject* ptr = children[i];
		ptr->Render();
	}

}

void UICanvas::CleanUp()
{
	for (int i = 0; i < children.size(); i++) {
		UIObject* o = children[i];
		o->CleanUp();
		DropChild(o);
	}
}

