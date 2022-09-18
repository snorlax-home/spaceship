#pragma once
#include <d3dx9.h>
#include <dinput.h>

class UIObject {
protected:
	LPDIRECT3DDEVICE9 d3dDevice;
	D3DXVECTOR2 relativePosition;
	int width;
	int height;
	int zIndex = 0;
	DIMOUSESTATE mouseState;
	RECT collisionRect;
public:
	// Constructor
	UIObject();

	// Destructor
	~UIObject();

	// Mutators
	virtual void SetD3DDevice(LPDIRECT3DDEVICE9 d3dDevice);
	virtual void SetRelativePosition(D3DXVECTOR2 relativePosition);
	virtual void SetWidth(int width);
	virtual void SetHeight(int height);
	virtual void SetZIndex(int zIndex);
	virtual void SetCollisionRect(RECT collisionRect);

	// Accessors
	virtual LPDIRECT3DDEVICE9 GetD3DDevice();
	virtual D3DXVECTOR2 GetRelativePosition();
	virtual int GetWidth();
	virtual int GetHeight();
	virtual int GetZIndex();
	virtual RECT GetCollisionRect();

	// Game loop placeholder
	virtual void InitUI() = 0;
	virtual void Update(DIMOUSESTATE mouseState) = 0;
	virtual void Render() = 0;
	virtual void CleanUp() = 0;

	// Preset functions
	virtual void UpdateUIPosition(D3DXVECTOR2 newPosition);
	// bool operator<(const UIObject& o) const;
};
