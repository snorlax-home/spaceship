#include "GameLevel.h"
#include "AudioManager.h"
#include "UIManager.h"
#include "UICanvas.h"
#include "UIFrame.h"
#include "UILabel.h"
#include "UIButton.h"

class MainMenu : public GameLevel {

private:
	UIFrame* mainFrame;

public:


	MainMenu(AudioManager* audioManager, UIManager* uiManager, IDirect3DDevice9* d3dDevice)
		: GameLevel(audioManager, uiManager, d3dDevice) {
		mainFrame = new UIFrame();
	}

	void InitLevel() {
		UICanvas* mainCanvas = new UICanvas();
		LPCSTR labelText = "Test";
		D3DXVECTOR2 initialPosition = D3DXVECTOR2(200, 200);
		UIObject* mainLabel = new UIButton(labelText, d3dDevice, initialPosition, 100, 50, 0, NULL);
		mainCanvas->AddChild(mainLabel);
		mainFrame->AddCanvas(*mainCanvas);
		mainFrame->InitUI();
		uiManager->AddFrame(*mainFrame);
	};

	void GetInput(BYTE diKeys, DIMOUSESTATE mouseState) {
		uiManager->Update(mouseState);
	};
	void Update(BYTE diKeys, DIMOUSESTATE mouseState) {
		GetInput(diKeys, mouseState);
	};
	void Render(LPD3DXSPRITE spriteBrush) {
		uiManager->Render();
	};
	void CleanUp() {
		uiManager->CleanUpFrame();
	};
};