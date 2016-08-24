
#include <d3dx9.h>

//header guard at start of header file
#ifndef CCamera_H
#define CCamera_H

class CCamera
{
public:
	CCamera::CCamera(int screenWidth, int screenHeight);
	CCamera::~CCamera();
	static void Transform(D3DXVECTOR2 viewPort, D3DXVECTOR2* position);		// real to directX
	static void InTransform(D3DXVECTOR2 viewPort, D3DXVECTOR2* inPosition);		// directX to real
	void SetPositionCamera(D3DXVECTOR2 position);
	D3DXVECTOR2 GetPositionCamera();
	RECT GetViewport();

private:
	D3DXVECTOR2 _position;
	int _screenWidth;
	int _screenHeight;
};
#endif

